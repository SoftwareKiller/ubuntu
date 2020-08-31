#pragma once

#include "../net/Buffer.h"
#include "../base/Timestamp.h"
#include "../net/Tcp_connection.h"
#include "../base/AsyncLogging.h"
#include <memory>

using namespace net;

class http_session {
public:
	http_session(std::shared_ptr<TcpConnection>& conn);
	~http_session() = default;

	http_session(const http_session& rhs) = delete;
	http_session& operator=(const http_session& rhs) = delete;

public:
	void onRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp reveiveTime);

	std::shared_ptr<TcpConnection> getConnectionPtr() {
		if (m_tempConn.expired())
			return nullptr;

		return m_tempConn.lock();
	}

	void send(const char* data, size_t length);

private:
	bool process(const std::shared_ptr<TcpConnection>& conn, const std::string& url, const std::string& param);

private:
	std::weak_ptr<TcpConnection> m_tempConn;
};
