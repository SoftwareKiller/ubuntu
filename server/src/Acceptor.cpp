#include "Acceptor.h"

Acceptor::Acceptor(const char* ip, uint16_t port)
    :addr_(ip, port),
    listenfd_(new Socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
{
    if(listenfd_->fd() == -1)
    {
        std::cerr << "create listen socket failed !" << std::endl;
        exit(EXIT_FAILURE);
    }

    listenfd_->setReuse();
    listenfd_->setNoDelay();
}

bool Acceptor::startlisten()
{
    listenfd_->bindAddress(&addr_);

    int ret = listen(listenfd_->fd(), SOMAXCONN);

    if(ret == -1)
    {
        std::cerr << "listen fail!" << std::endl;
        return false;
    }

    return true;
}

int Acceptor::AcceptNewClient()
{
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    int client_fd = accept(listenfd_->fd(), (struct sockaddr*)&clientAddr, &len);
    if(client_fd == -1)
    {
        std::cerr << "accept new connect fail!" << std::endl;
        return client_fd;
    }

    int oldSocketFlag = fcntl(client_fd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if(fcntl(listenfd_->fd(), F_SETFL, newSocketFlag) == -1)
    {
        std::cerr << "fcntl listenfd fail" << std::endl;
        close(client_fd);
        return -1;
    }
    return client_fd;
}
