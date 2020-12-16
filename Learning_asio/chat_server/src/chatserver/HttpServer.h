#pragma once

#include <memory>
#include <mutex>
#include <list>
#include "../net/EventLoop.h"
#include "../net/Tcp_server.h"
#include "http_session.h"

using namespace net;

class HttpServer final {
public:
	HttpServer() = default;
	~HttpServer() = default;

	HttpServer(const HttpServer& rhs) = delete;
	HttpServer& operator =(const HttpServer& rhs) = delete;

public:
	bool init(short port);
	void uninit();

	void onConnected(std::shared_ptr<TcpConnection> conn);

	void onDisconnected(const std::shared_ptr<TcpConnection>& conn);

private:
	std::unique_ptr<TcpServer> m_server;
	std::list<std::shared_ptr<http_session>> m_sessions;
	std::mutex m_sessionMutex;;
};
