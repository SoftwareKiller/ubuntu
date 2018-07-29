#include<sys/socket.h>
#include<sys/select.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int startup(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("bind");
        exit(3);
    }

    if(listen(sock, 5) < 0)
    {
        perror("listen");
        exit(4);
    }

    return sock;
}

void serviceIO(fd_set* rfds, int* fd_arr, int num)
{
    int i = 0;
    for(; i < num; ++i)
    {
        if(fd_arr[i] == -1)
            continue;

        if( i==0 && FD_ISSET(fd_arr[i], rfds)) //监听套接字,进入这条分支，说明select已经得到一个连接
        {
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            int sock = accept(fd_arr[i], (struct sockaddr*)&client, &len);
            if( sock < 0 )
            {
                perror("accept");
                continue;
            }
            printf("Get a new client\n");
            int j = 1;
            for(; j < num; ++j)
            {
                if(fd_arr[j] == -1)
                    break;
            }
            if(j < num)
            {
                fd_arr[j] = sock;
            }else{
                printf("fd_arr is full\n");
                close(sock);
                continue;
            }
            continue;
        }

        if(FD_ISSET(fd_arr[i], rfds))
        {
            char buf[1024];
            memset(buf, 0, sizeof(buf));
            ssize_t s = read(fd_arr[i], buf, sizeof(buf)-1);
            if(s < 0)
            {
                perror("read");
                fd_arr[i] = -1;
                close(fd_arr[i]);
            }else if(s == 0)
            {
                printf("client quit\n");
                fd_arr[i] = -1;
                close(fd_arr[i]);
            }else{
                buf[s] = '\0';
                printf("%s\n", buf);
                write(fd_arr[i], buf, s);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if(2 != argc)
    {
        printf("Usage: %s [PORT]\n", argv[0]);
        return 1;
    }

    int listen_sock = startup(atoi(argv[1]));
    int fd_arr[sizeof(fd_set) * 8];
    int num = sizeof(fd_arr)/sizeof(fd_arr[0]);

    int i = 0;
    for(; i < num; ++i) //将套接字数组初始化
    {
        fd_arr[i] = -1;
    }

    fd_arr[0] = listen_sock;    //监听套接字（被动）

    fd_set rfds;    //读事件集合
    int maxfd = -1; //最大套接字

    for( ; ; )
    {
        struct timeval timeout = {0, 0};
        for(i = 0; i < num; ++i)
        {
            if( fd_arr[i] == -1 )
                continue;

            FD_SET(fd_arr[i], &rfds);
            if(maxfd < fd_arr[i])   //找出最大套接字
                maxfd = fd_arr[i];
        }

        switch(select(maxfd+1, &rfds, NULL, NULL, NULL))
        {
        case 0: //超时设置为NULL，这种情况不可能出现
            printf("timeout\n");
            break;
        case -1:
            perror("select");
            break;
        default:
            serviceIO(&rfds, fd_arr, num);
            break;
        }
    }
}
