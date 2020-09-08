#pragma once

#include <memory>
#include "../net/Tcp_connection.h"

using namespace net;

class TcpSession {
public:
	TcpSession(const std::weak_ptr<TcpConnection>& tempConn);
	~TcpSession();

	TcpSession(const TcpSession& rhs) = delete;
	TcpSession& operator =(const TcpSession& rhs) = delete;

	std::shared_ptr<TcpConnection> getConnectionPtr() {
		if (tempConn_.expired())
			return nullptr;

		return tempConn_.lock();
	}

	void send(int32_t cmd, int32_t seq, const std::string& data);
	void send(int32_t cmd, int32_t seq, const char* data, int32_t len);
	void send(const std::string& p);
	void send(const char* p, int32_t length);

private:
	void sendPackage(const char* p, int32_t length);
protected:
	std::weak_ptr<TcpConnection> tempConn_;
};
