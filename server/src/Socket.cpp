#include "Socket.h"
#include "IAddress.h"

Socket::Socket(int fd)
    :fd_(fd)
{
}

Socket::~Socket()
{
    close(fd_);
}

void Socket::bindAddress(Address* localaddr)
{
    int ret = bind(fd_, (struct sockaddr*)&localaddr->getAddr(), localaddr->getAddrLen());
    if(ret == -1)
    {
        std::cerr << "bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Socket::setReuse()
{
    int on = 1;
    setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on, static_cast<socklen_t>(sizeof(on)));
    setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &on, static_cast<socklen_t>(sizeof(on)));
}

void Socket::setNoDelay()
{
    int on = 1;
    setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &on, static_cast<socklen_t>(sizeof(on)));
}

