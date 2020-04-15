#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <cerrno>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenfd == -1)
    {
        cerr << "socket" << endl;
        return -1;
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (void*)on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (void*)on, sizeof(on));

    int oldSocketFlag = fcntl(listenfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if(fcntl(listenfd, F_SETFL, newSocketFlag) == -1)
    {
        cerr << "fcntl error" << endl;
        return -1;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(20000);

    int ret = bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(ret == -1)
    {
        cerr << "bind error" << endl;
        return -1;
    }

    ret = listen(listenfd, SOMAXCONN);
    if(ret == -1)
    {
        cerr << "listen error" << endl;
        return -1;
    }

    int epollfd = epoll_create(1);
    if(epollfd == -1)
    {
        cerr << "epoll create epollfd error" << endl;
        return -1;
    }

    epoll_event listen_epollfd;
    listen_epollfd.data.fd = listenfd;
    listen_epollfd.events |= EPOLLIN;
    //listen_epollfd.events |= EPOLLET;

    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &listen_epollfd);
    if(ret == -1)
    {
        cerr << "epoll_ctl error" << endl;
        close(listenfd);
        return -1;
    }

    epoll_event fds[1024];
    for(;;)
    {
        int n = epoll_wait(epollfd, fds, 1024, 1000);
        if(n < 0)
        {
            if(errno == EINTR)
                continue;

            return -1;
        }
        else if(n == 0)
        {
            //timeout
            continue;
        }

        for(size_t i = 0; i < n; ++i)
        {
            if(fds[i].events & EPOLLIN)
            {
                if(fds[i].data.fd == listenfd) //新连接
                {
                    struct sockaddr_in clientaddr;
                    socklen_t len = sizeof(clientaddr);
                    int new_client = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
                    if(new_client == -1)
                    {
                        cerr << "accept error" << endl;
                        continue;
                    }

                    int oldSocketFlag = fcntl(new_client, F_GETFL, 0);
                    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
                    if(fcntl(new_client, F_SETFL, newSocketFlag) == -1)
                    {
                        cerr << "new client fcntl error" << endl;
                        close(new_client);
                        continue;
                    }

                    epoll_event client_epollfd;
                    client_epollfd.data.fd = new_client;
                    client_epollfd.events |= EPOLLIN;
                    client_epollfd.events |= EPOLLET;
                    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, new_client, &client_epollfd);
                    if(ret == -1)
                    {
                        close(new_client);
                        cerr << "new client epoll add error" << endl;
                        continue;
                    }

                    cout << "accept new client, add epoll event success, clientfd is : " << new_client << endl;
                }
                else  //新数据
                {
                    char buf[32] = { 0 };
                    while(true)
                    {
                        int data_length = read(fds[i].data.fd, buf, sizeof(buf));
                        if(data_length < 0)
                        {
                            if(errno != EWOULDBLOCK && errno != EINTR)
                            {
                                cerr << "read error" << endl;
                                close(fds[i].data.fd);
                                epoll_ctl(epollfd, EPOLL_CTL_DEL, fds[i].data.fd, &fds[i]);
                                break;
                            }
                            else{
                                continue;
                            }
                        }
                        else if(data_length == 0)
                        {
                            cout << "client quit, clientfd is : " << fds[i].data.fd << endl;;
                            close(fds[i].data.fd);
                            epoll_ctl(epollfd, EPOLL_CTL_DEL, fds[i].data.fd, &fds[i]);
                            break;
                        }else{
                            buf[data_length] = 0;
                            cout << "recv client data, data is : " << buf << " ,data length is " << data_length << endl;
                            memset(buf, 0, sizeof(buf));
                        }
                    }
                }
            }
            else if(fds[i].events & EPOLLOUT)
            {
            }
            else if(fds[i].events & EPOLLERR)
            {
                //TODO:暂不处理
            }
        }
    }

    close(listenfd);
    return 0;
}

