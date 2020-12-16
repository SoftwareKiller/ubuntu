#pragma once
#include "stdafx.h"
#include <cerrno>
#include <vector>
#include <set>
#include <iostream>
#include "Acceptor.h"
#include "IAddress.h"

class Event
{
public:
    Event(const char* ip, unsigned short port);

    void loop();

private:
    void read_event(int fd);

    void CanelClient(int fd);

    bool newConnect();

    const size_t getOnlineUser()
    {
        return fds_.size();
    }

    int poller();

    void readable(epoll_event* eventfd);

private:
    int                                     epollfd_;
    std::vector<epoll_event>                events_;
    Acceptor                                accept_;
    std::set<int>                           fds_;
    bool                                    quit_;
};

