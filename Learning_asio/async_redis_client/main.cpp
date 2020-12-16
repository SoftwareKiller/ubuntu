#include "client.h"
#include "parser.h"
#include "encode.hpp"

int main()
{
    asio::io_context ios;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 6379);
    auto client = std::make_shared<RedisClient>(ios, ep);

    client->Start();

    std::thread t([&ios]() { ios.run(); });

    std::cout << ep.address().to_string() << ":" << ep.port() << ">" << std::flush;
    std::string line;
    while(std::getline(std::cin, line))
    {
        std::string bulk_string = Encode::EncodeInput(line);
        client->Send(bulk_string);
    }

    t.join();

    return 0;
}
