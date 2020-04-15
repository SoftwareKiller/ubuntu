#pragma once
#include "stdafx.h"

class Address;

class Socket
{
public:
    Socket(int fd);
    ~Socket();

    const int fd()
    {
        return fd_;
    }

    void bindAddress(Address* localaddr);

    void setReuse();
    
    void setNoDelay();

private:
    const int         fd_;
};

