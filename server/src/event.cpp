#include "event.h"
#include <cstring>

Event::Event(const char* ip, unsigned short port):
    epollfd_(epoll_create(1024)),
    accept_(ip, port)
{
    if(epollfd_ == -1)
    {
        std::cerr << "epoll create failed !" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(!accept_.startlisten())
    {
        std::cerr << "Acceptor init failed!!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    epoll_event listen_event;
    listen_event.data.fd = accept_.fd();
    listen_event.events |= EPOLLIN;

    events_.push_back(listen_event);

    if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, accept_.fd(), &events_[0]) == -1)
    {
        std::cerr << "epoll ctl add listent event failed" << std::endl;
        close(accept_.fd());
        exit(EXIT_FAILURE);
    }
}

void Event::loop()
{
    quit_ = false;
    while(!quit_)
    {
        int n = poller();
        if(n == 0)
        {
            continue;
        }

        for(int i = 0; i < n; ++i)
        {
            if(events_[i].events & EPOLLIN)
            {
                if(events_[i].data.fd == accept_.fd())
                {
                    newConnect();
                }
                else
                {
                    read_event(events_[i].data.fd);
                }
            }
        }
    }
}

void Event::read_event(int fd)
{
    char buf[1024] = { 0 };
    int ret = read(fd, buf, sizeof(buf));
    if(ret < 0)
    {
        if(errno == EWOULDBLOCK)
        {
            std::cerr << "Read message is null!" << std::endl;
            return;
        }else if(errno == EINTR)
        {
            std::cerr << "This Error from os singo!" << std::endl;
            return;
        }else{
            std::cerr << "Read error, client " << fd <<" disconnect!" << std::endl;
            CanelClient(fd);
        }
    }else if(ret == 0)
    {
        std::cout << "client quit, clientfd is : " << fd << std::endl;
        CanelClient(fd);
    }
    else
    {
        std::cout << "recv client data, data length is : " << ret << "data is :" << buf << std::endl;
        char outbuf[512] = { 0 };
        const char* hello = "<h1> hello </h1>";
        snprintf(outbuf, sizeof(outbuf), "HTTP/1.0 200 OK\n Content-Length:%lu\n\n%s", strlen(hello), hello);
        int remain = strlen(outbuf);
        int written = 0;
        while(remain > 0)
        {
            written = write(fd, outbuf, strlen(outbuf));
            remain -= written;
        }
    }
}

void Event::CanelClient(int fd)
{
    auto it = fds_.find(fd);
    if(it != fds_.end())
        fds_.erase(it);

    for(std::vector<epoll_event>::iterator it = events_.begin(); it != events_.end(); ++it)
    {
        if(fd == it->data.fd)
        {
            epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &(*it));
            events_.erase(it);
            break;
        }
    }
}

bool Event::newConnect()
{
    int clientfd = accept_.AcceptNewClient();
    if(clientfd == -1)
    {
        std::cerr << "Accept new client failed" << std::endl;
        return false;
    }
    std::cout << "new client connect! clientfd is : " << clientfd << std::endl;
    epoll_event client_event;
    client_event.data.fd = clientfd;
    readable(&client_event);
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, clientfd, &client_event);
    events_.push_back(client_event);
    fds_.insert(clientfd);
}

int Event::poller()
{
    int ret = epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), 5000);
    if(ret < 0)
    {
        if(errno == EINTR)
        {
            std::cerr << "epoll wait error, from single!" << std::endl;
            return -1;
        }
        close(accept_.fd());
        exit(EXIT_FAILURE);
    }
    else if(ret == 0)
    {
        std::cout << "epoll wait time out..." << std::endl;
        std:: cout << "event size: " << events_.size() << std::endl;
        return 0;
    }

    if(static_cast<unsigned int>(ret) == events_.size())
    {
        events_.resize( events_.size() * 2 );
    }


    return ret;
}

void Event::readable(epoll_event* eventfd)
{
    eventfd->events |= EPOLLIN;
}

