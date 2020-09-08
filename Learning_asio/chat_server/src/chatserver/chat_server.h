#pragma once
#include <memory>
#include <list>
#include <mutex>
#include <atomic>
#include "../net/Tcp_server.h"
#include "chat_session.h"

using namespace net;

enum CLIENT_TYPE {
	CLIENT_TYPE_UNKNOW,
	CLIENT_TYPE_PC,
	CLIENT_TYPE_ANDROID,
};

struct StoredUserInfo {
	int32_t        userid;
	std::string    username;
	std::string    password;
	std::string    nickname;
};

class ChatServer final {
public:
	ChatServer();
	~ChatServer() = default;

	ChatServer(const ChatServer & rhs) = delete;
	ChatServer& operator =(const ChatServer & rhs) = delete;

	bool init(short port);
	void uninit();

private:
	void onConnected(std::shared_ptr<TcpConnection> conn);
	void onDisconnetion(const std::shared_ptr<TcpConnection>& conn);

private:
	std::unique_ptr<TcpServer>                m_server;
	std::list<std::shared_ptr<chat_session>>  m_sessions;
	std::mutex                                m_sessionMutex;
	std::atomic_bool                          m_logPackageBinary;
};
