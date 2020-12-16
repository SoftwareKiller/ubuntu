#include "chat_server.h"
#include "../base/AsyncLogging.h"

ChatServer::ChatServer() {
	m_logPackageBinary = false;
}

bool ChatServer::init(short port) {
	m_server.reset(new TcpServer(port));
	m_server->setConnecttionCallback(std::bind(&ChatServer::onConnected, this, std::placeholders::_1));

	m_server->Initialize();

	return true;
}

void ChatServer::uninit() {
		m_server->Stop();
}

void ChatServer::onConnected(std::shared_ptr<TcpConnection> conn) {
	if (conn->connected()) {
		LOG_INFO("client connected chat_server:%d", conn->peerEp().port());

		std::shared_ptr<chat_session> spSession = make_shared<chat_session>(conn, conn->getId());
		conn->setMessageCallback(std::bind(&chat_session::onRead, spSession.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	
		std::lock_guard<std::mutex> guard(m_sessionMutex);
		m_sessions.push_back(spSession);
	}
	else
	{
		onDisconnetion(conn);
	}
}

void ChatServer::onDisconnetion(const std::shared_ptr<TcpConnection>& conn) {
	conn->OnClose();
}
