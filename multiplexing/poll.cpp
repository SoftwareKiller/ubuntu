#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <cerrno>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        cerr << "socket" << endl;
        return -1;
    }

    int oldSocketFlag = fcntl(sockfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if(fcntl(sockfd, F_SETFL, newSocketFlag) == -1)
    {
        cerr << "fcntl" << endl;
        return -1;
    }

    int on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)on, sizeof(on));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (void *)on, sizeof(on));

    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localaddr.sin_port = htons(20000);
    int ret = bind(sockfd, (struct sockaddr*)&localaddr, sizeof(localaddr));
    if(ret == -1)
    {
        cerr << "bind" << endl;
        return -1;
    }

    ret = listen(sockfd, SOMAXCONN);
    if(ret == -1)
    {
        cerr << "listen" << endl;
        return -1;
    }

    vector<pollfd> fds;
    pollfd listenfd;
    listenfd.fd = sockfd;
    listenfd.events |= POLLIN;
    listenfd.revents = 0;
    fds.push_back(listenfd);

    bool exit_fd;
    int n;

    while(true)
    {
        exit_fd = false;
        n = poll(&fds[0], fds.size(), 1000);
        if(n < 0)
        {
            if(errno != EINTR)
            {
                cerr << "poll" << endl;
                continue;
            }
            break;
        }
        else if(n == 0)
        {
            //cout << "poll time out" << endl;
            continue;
        }

        for(size_t i = 0; i < fds.size(); ++i)
        {
            if(fds[i].revents & POLLIN)
            {
                if(fds[i].fd == sockfd) //有新连接
                {
                    struct sockaddr_in clientaddr;
                    clientaddr.sin_family = AF_INET;
                    socklen_t len = sizeof(clientaddr);
                    int new_client = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
                    if(new_client == -1)
                    {
                        cerr << "accept" << endl;
                        continue;
                    }

                    int oldSocketFlag = fcntl(new_client, F_GETFL, 0);
                    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
                    if(fcntl(new_client, F_SETFL, newSocketFlag) < 0)
                    {
                        cerr << "fcntl" << endl;
                        close(new_client);
                        continue;
                    }

                    cout << "new connect, clientfd is " << new_client << endl;

                    pollfd clientfd;
                    clientfd.fd = new_client;
                    clientfd.events |= POLLIN;
                    clientfd.revents = 0;
                    fds.push_back(clientfd);
                }else  //有新数据
                {
                    char buf[64] = { 0 };
                    int data_length = read(fds[i].fd, buf, sizeof(buf));
                    if(data_length <= 0)
                    {
                        if(errno == EAGAIN || errno == EINTR)
                        {
                            cout << "This Error by Tcp Window is to small or From Singo!" << endl;
                            continue;
                        }
                        else
                        {
                            for(vector<pollfd>::iterator it = fds.begin(); it != fds.end(); ++it)
                            {
                                if(it->fd == fds[i].fd)
                                {
                                    cout << "clientfd " << fds[i].fd <<" disconnect" << endl;
                                    close(fds[i].fd);
                                    fds[i].fd = -1;
                                    exit_fd = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "read data successfully, data From client : " << fds[i].fd << " data is :"
                            << buf << endl;
                    }
                }
            }
            else if(fds[i].revents & POLLERR)
            {
                //TODO: 暂时不处理
            }
        }

        if(exit_fd)
        {
            for(vector<pollfd>::iterator it = fds.begin(); it != fds.end();)
            {
                if(it->fd == -1)
                    fds.erase(it);
                else
                    ++it;
            }
        }
    }

    for(vector<pollfd>::iterator it = fds.begin(); it != fds.end(); ++it)
    {
        close(it->fd);
    }
    return 0;
}

