#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        cerr << "socket" << endl;
        return 1;
    }

    int ret = -1;

    /*int oldSocketFlag = fcntl(listenfd, F_GETFL, 0);
      int newSocketFlag = oldSocketFlag | O_NONBLOCK;
      int ret = fcntl(listenfd, F_SETFL, newSocketFlag);
      if(ret < 0)
      {
      cerr << "fcntl" << endl;
      return 2;
      }*/

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on));

    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localaddr.sin_port = htons(20000);
    ret = bind(listenfd, (struct sockaddr*)&localaddr, sizeof(localaddr));
    if(ret < 0)
    {
        cerr << "bind" << endl;
        return 3;
    }

    ret = listen(listenfd, SOMAXCONN);
    if(ret < 0)
    {
        cerr << "listen" << endl;
        return 4;
    }

    int maxfd = listenfd;
    vector<int> clientfds;

    while(true)
    {
        fd_set readfds;
        FD_ZERO(&readfds);  //将可读时间全部清零

        FD_SET(listenfd, &readfds);  //将监听fd加入可读事件中

        size_t clientfd_len = clientfds.size();
        for(size_t i = 0; i < clientfd_len; ++i)
        {
            if(clientfds[i] != -1)
            {
                FD_SET(clientfds[i], &readfds);
            }
        }

        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        ret = select(maxfd + 1, &readfds, nullptr,nullptr, &timeout);
        if(ret < 0)
        {
            cerr << "select" << endl;
            return 5;
        }
        else if(ret == 0)
        {
            //timeout
            continue;
        }
        else
        {
            if(FD_ISSET(listenfd, &readfds))  //来了新连接
            {
                struct sockaddr_in clientaddr;
                clientaddr.sin_family = AF_INET;
                socklen_t len = sizeof(clientaddr);
                int client;
                if((client = accept(listenfd, (struct sockaddr*)&clientaddr, &len)) < 0)
                {
                    cerr << "acceppt" << endl;
                    continue;
                }

                clientfds.push_back(client);
                if(maxfd < client)
                    maxfd = client;
            }
            else
            {
                size_t len = clientfds.size();
                for(int i = 0; i < len; ++i)
                {
                    if(clientfds[i] != -1 && FD_ISSET(clientfds[i], &readfds))
                    {
                        char buf[64] = { 0 };
                        ret = read(clientfds[i], buf, sizeof(buf));
                        //事实上这里应该close每个ret==0的连接，
                        //但是这里为了让打印的客户端clientfd递增的明显一点，
                        //没有关闭，而是置为-1
                        if(ret <= 0 && errno != EINTR)
                        {
                            cerr << "read" << endl;
                            clientfds[i] = -1;
                            continue;
                        }
                        cout << "From clientfd: " << clientfds[i] << " data : " << buf << endl;
                    }
                }
            }
        }
    }

    for(size_t i = 0; i < clientfds.size(); ++i)
        close(clientfds[i]);

    close(listenfd);
    return 0;
}

