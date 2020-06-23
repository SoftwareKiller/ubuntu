#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <memory>
#include <deque>
#include "parser.h"
#include <asio.hpp>

class RedisClient : public std::enable_shared_from_this<RedisClient>
{
public:
    RedisClient(asio::io_context& io, asio::ip::tcp::endpoint ep)
        :io_context_(io), socket_(io), ep_(ep)
    {
    }

    void Start();

    void RecvData(const asio::error_code& ec, size_t len);

    void Send(const std::string& line);

private:
    void SendQueue();

private:
    asio::io_context& io_context_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::endpoint ep_;
    char recv_buff_[1024];
    std::string send_buff_;
    std::deque<std::string> requests_;
    std::shared_ptr<ReplyItem> parse_item_;
};

#endif
