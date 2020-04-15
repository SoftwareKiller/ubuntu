#pragma once
#include "stdafx.h"
#include <iostream>
#include "Socket.h"
#include "IAddress.h"

class Acceptor
{
public:
    Acceptor(const char* ip, uint16_t port);
    ~Acceptor() = default;

    bool startlisten();

    int AcceptNewClient();


    const int fd()
    {
        return listenfd_->fd();
    }
    
private:
    std::unique_ptr<Socket>         listenfd_;
    Address                         addr_;
};

