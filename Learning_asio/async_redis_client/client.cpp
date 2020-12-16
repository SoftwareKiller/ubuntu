#include "client.h"

void RedisClient::Start()
{
    auto self = shared_from_this();
    socket_.async_connect(ep_, [self, this](const asio::error_code& ec)
                          {
                              if(ec)
                              {
                                  std::cerr << "connect error" << std::endl;
                                  return;
                              }

                              auto self = shared_from_this();
                              socket_.async_receive(asio::buffer(recv_buff_), bind(&RedisClient::RecvData, this, std::placeholders::_1,
                                                                                   std::placeholders::_2));
                          });
}

void RedisClient::RecvData(const asio::error_code& ec, size_t len)
{
    if(ec)
    {
        socket_.close();
        std::cerr << "receive failed, ec:" << ec.message() << std::endl;
        return;
    }

    for(char* p = recv_buff_; p < recv_buff_ + len; ++p)
    {
        if(!parse_item_)
        {
            parse_item_ = ReplyItem::CreateItem(*p);
            continue;
        }

        ParseResult ret = parse_item_->Result(*p);
        if(ret == ParseResult::FINISHED)
        {
            std::cout << parse_item_->ToString() << std::endl;
            std::cout << ep_.address().to_string() << ":" << ep_.port() << ">" << std::flush;
            parse_item_.reset();
        }
        else if(ret == ParseResult::ERROR)
        {
            std::cout << "parse error at " << *p << ", pos = " << (p-recv_buff_) << std::endl;
            std::cout << ep_.address().to_string() << ":" << ep_.port() << ">" << std::flush;
            parse_item_.reset();
        }
    }

    socket_.async_receive(asio::buffer(recv_buff_), bind(&RedisClient::RecvData, this, std::placeholders::_1,
                                                                                   std::placeholders::_2));
}

void RedisClient::Send(const std::string& line)
{
    auto self = shared_from_this();
    /*io_context_.post([self, this, line]()
                     {
                         SendQueue();
                     });*/

    asio::post(io_context_, [self, this, line]()
               {
                   requests_.push_back(line);
                   SendQueue();
               });
}

void RedisClient::SendQueue()
{
    auto self = shared_from_this();
    if(!requests_.empty())
    {
        send_buff_.clear();
        send_buff_ = requests_.front();
        requests_.pop_front();
        asio::async_write(socket_, asio::buffer(&send_buff_[0], send_buff_.length()), [self, this](const asio::error_code& ec, size_t length)
                          {
                              if(ec)
                              {
                                  socket_.close();
                                  std::cerr<< "write failed, ec:" << ec.message() << std::endl;
                                  return;
                              }

                              std::cout << "send msg" << std::endl;

                              auto self = shared_from_this();
                              //io_context_.post([self, this]()
                              asio::post(io_context_, [self, this]()
                                               {
                                                   SendQueue();
                                               });
                          });
    }
}
