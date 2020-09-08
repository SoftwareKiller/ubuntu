#include "Tcp_connection.h"

#include <functional>
#include <thread>
#include <sstream>
#include <errno.h>
#include "../base/AsyncLogging.h"

using namespace net;

void net::defaultConnectionCallback(const TcpConnectionPtr& conn) {
	LOG_INFO("%d -> is %d", conn->localEp().port(), conn->peerEp().port());
}

void net::defaultMessageCallback(const TcpConnectionPtr&, Buffer* buf, Timestamp) {
	buf->retrieveAll();
}

TcpConnection::TcpConnection(asio::io_context& io, Session_Mgr& session_mrg, const asio::ip::tcp::endpoint local)
	:io_context_(io)
	,session_mrg_(session_mrg)
	,socket_(io)
	,local_(local)
	,connection_id_(0)
	,messageCallback_(defaultMessageCallback)
	,state_(StateE::kDisconnected)
{
}

TcpConnection::~TcpConnection()
{
	LOG_INFO("TcpConnection::dtor:%lld", connection_id_);
}

void TcpConnection::start() {
	setState(StateE::kConnected);
	connectionCallback_(shared_from_this());
	do_read();
}

void TcpConnection::OnClose() {
	setState(StateE::kDisconnected);
	session_mrg_.DelSession(connection_id_);
	socket_.close();
}

void TcpConnection::send(const string& message) {
	auto p = shared_from_this();

	LOG_INFO("Send message:%s", message.c_str());
	socket_.async_write_some(asio::buffer(message.data(), message.size()), [p, this, message](asio::error_code err, size_t len) {
			if (err) {
				LOG_ERROR("write error:%s", err.message().c_str());
				OnClose();
				return;
			}

			if (len < message.size()) {
				outputBuffer_.append(message.data() + len);
				do_send();
			}
		});
}

void TcpConnection::send(const char* data, size_t len) {
	if (state_ == kConnected) {
		string message(static_cast<const char*>(data), len);
		send(message);
	}
}

void TcpConnection::do_read() {
	auto p = shared_from_this();

	LOG_INFO("connection start recive");

	socket_.async_read_some(asio::buffer(inputBuffer_.peek(), inputBuffer_.writableBytes()), [p, this](const asio::error_code& err, size_t len) {
			if (err) {
				LOG_ERROR("recv error: %s", err.message().c_str());
				OnClose();
				return;
			}

			inputBuffer_.produce(len);

			LOG_INFO("buffer length : %d, input:%d", inputBuffer_.readable(), len);

			if (messageCallback_ == nullptr)
				return;
			messageCallback_(shared_from_this(), &inputBuffer_, Timestamp::now());
		});
}

void TcpConnection::do_send() {
	auto self = shared_from_this();

	socket_.async_write_some(asio::buffer(outputBuffer_.peek(), outputBuffer_.readable()), [self, this](asio::error_code err, size_t len) {
			if (err) {
				LOG_ERROR("write error:%s", err.message().c_str());
				OnClose();
				return;
			}

			if (len == outputBuffer_.readable()) {
				outputBuffer_.retrieveAll();
			}
			else if (len < outputBuffer_.readable()) {
				outputBuffer_.retrieve(len);
				do_send();
			}
		});
}
