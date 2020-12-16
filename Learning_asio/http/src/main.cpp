#include <iostream>
#include <string>
#include <memory>
#include "asio.hpp"

using namespace std;

class connection : public enable_shared_from_this<connection>{
public:
	connection(asio::io_context& io) : socket_(io) {}

	void start() {
		auto p = shared_from_this();

		asio::async_read_until(socket_, asio::dynamic_buffer(request_), "\r\n\r\n", [p, this](const asio::error_code& err, size_t len) {
			if (err) {
				cout << "recv error:" << err.message() << endl;
				return;
			}

			string first_line = request_.substr(0, request_.find("\r\n"));
			cout << first_line << endl;

			char response[] = "HTTP/1.0 200 OK\r\n\r\n<html><h1>asio 666</h1></html>";

			asio::async_write(socket_, asio::buffer(response), [p, this](const asio::error_code& err, size_t len) {
				if (err) {
					cout << "response error" << err.message() << endl;
					return;
				}
				socket_.close();
			});
		});
	}

	asio::ip::tcp::socket& fd() { return socket_; }
private:
	asio::ip::tcp::socket socket_;
	string request_;
};

class http_server {
public:
	http_server(asio::io_context& io, asio::ip::tcp::endpoint ep):io_(io), acceptor_(io_, ep) {}

	void start() {
		auto connect = make_shared<connection>(io_);
		acceptor_.async_accept(connect->fd(), [connect, this](const asio::error_code& err) {
			if (err) {
				cout << "accept error:" << err.message() << endl;
				return;
			}
			connect->start();
			start();
		});
	}
private:
	asio::io_context& io_;
	asio::ip::tcp::acceptor acceptor_;
};

int main() {
	asio::io_context io;
	asio::ip::tcp::endpoint ep(asio::ip::make_address("127.0.0.1"), 20000);
	http_server server(io, ep);
	server.start();
	io.run();
	return 0;
}
