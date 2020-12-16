#pragma once
#include "stdafx.h"
#include <string>

class Address
{
public:
    Address(const char* IPaddress, unsigned short port);
    ~Address() = default;

    std::string toIp();

    unsigned short toPort();

    struct sockaddr_in& getAddr();

    const socklen_t getAddrLen()
    {
        return sizeof(address);
    }

private:
    struct sockaddr_in address;
};

