#define BOOST_ASIO_NO_DEPRECATED
#include <iostream>
#include <vector>
#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/deadline_timer.hpp"

void Print(boost::system::error_code ec,
           boost::asio::deadline_timer* timer,
           int* count) {
    if(*count < 3) {
        std::cout << "Hello World\n";
        ++(*count);
    
        timer->expires_at(timer->expires_at() + boost::posix_time::seconds(1));
    
        timer->async_wait(std::bind(&Print, std::placeholders::_1, timer, count));
    }


}


void Session(boost::asio::ip::tcp::socket socket) {
    while(true) {
        std::vector<char> data(1024);

        boost::system::error_code ec;
        std::size_t length = socket.read_some(boost::asio::buffer(data), ec);

        if(ec == boost::asio::error::eof) {
            std::cout << "client quit!\n";
            break;
        }else if(ec) {

        }

        boost::asio::write(socket, boost::asio::buffer(data, length));
    }
}

#if 0
int main() {
    boost::asio::io_context ioc;
    boost::asio::deadline_timer timer(ioc, boost::posix_time::seconds(1));
    int count = 0;
    timer.async_wait(std::bind(&Print, std::placeholders::_1, &timer, &count));
    ioc.run();
    return 0;
}
#endif

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<port>" << std::endl;
        return 1;
    }

    unsigned short port = std::atoi(argv[1]);
    boost::asio::io_context ioc;

    boost::asio::ip::tcp::acceptor acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    while(true) {
        Session(acceptor.accept());
    }
    return 0;
}


