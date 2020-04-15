#include "stdafx.h"
#include "IAddress.h"

Address::Address(const char* IPaddress, unsigned short port)
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IPaddress);
    address.sin_port = htons(port);
}

std::string Address::toIp()
{
    std::string ipstr = inet_ntoa(address.sin_addr);
    return ipstr;
}

unsigned short Address::toPort()
{
    return ntohs(address.sin_port);
}

struct sockaddr_in& Address::getAddr()
{
    return address;
}

