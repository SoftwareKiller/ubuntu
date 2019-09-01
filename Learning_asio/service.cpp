#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <boost/array.hpp>

using namespace std;
using namespace boost::asio;

#if 0
io_service io_s;
ip::tcp::resolver resolver(io_s);
ip::tcp::socket sock(io_s);
boost::array<char, 4096> buf;

void read_hander(const boost::system::error_code &ec, size_t bytes_transferred)
{
    if(!ec)
    {
        cout << string(buf.data(), bytes_transferred) << endl;
        sock.async_read_some(buffer(buf), read_hander);
    }
}

void connect_hander(const boost::system::error_code &ec)
{
    if(!ec)
    {
        write(sock, buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
        sock.async_read_some(buffer(buf), read_hander);
    }
}

void resolve_hander(const boost::system::error_code &ec, ip::tcp::resolver::iterator it)
{
    if(!ec)
    {
        sock.async_connect(*it, connect_hander);
    }
}

int main()
{
    ip::tcp::resolver::query qu("www.highscore.de", "80");
    resolver.async_resolve(qu, resolve_hander);
    io_s.run();
}
#endif

io_service io_s;
ip::tcp::endpoint ep(ip::tcp::v4(), 8888);
ip::tcp::acceptor ap(io_s, ep);
ip::tcp::socket sock(io_s);
string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\n Hello World!";

void write_handler(const boost::system::error_code& ec, size_t bytes_transferred)
{}

void accept_hanler(const boost::system::error_code &ec)
{
    if(!ec)
    {
        async_write(sock, buffer(data), write_handler);
    }
}

int main()
{
    ap.listen();
    ap.async_accept(sock, accept_hanler);
    io_s.run();
}


