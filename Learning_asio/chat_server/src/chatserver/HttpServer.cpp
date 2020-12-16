#include "HttpServer.h"
#include "http_session.h"

bool HttpServer::init(short port) {
	m_server.reset(new TcpServer(port));
	m_server->setConnecttionCallback(std::bind(&HttpServer::onConnected, this, std::placeholders::_1));
	LOG_INFO("m_server set callback");

	m_server->Initialize();

	return true;
}

void HttpServer::uninit() {
	if (m_server)
		m_server->Stop();
}

void HttpServer::onConnected(std::shared_ptr<TcpConnection> conn) {
	if (conn->connected()) {
		std::shared_ptr<http_session> spSession = make_shared<http_session>(conn);
		
		LOG_INFO("HTTP SERVER ON CONNECTION");
		conn->setMessageCallback(std::bind(&http_session::onRead, spSession.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		{
			std::lock_guard<std::mutex> guard(m_sessionMutex);
			m_sessions.push_back(spSession);
		}
	}
	else {
		onDisconnected(conn);
	}
}

void HttpServer::onDisconnected(const std::shared_ptr<TcpConnection>& conn) {
	std::lock_guard<std::mutex> guard(m_sessionMutex);

	for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
	{
		if ((*iter)->getConnectionPtr() == NULL)
		{
			LOG_ERROR("connection is NULL");
			break;
		}

		//通过比对connection对象找到对应的session
		if ((*iter)->getConnectionPtr() == conn)
		{
			m_sessions.erase(iter);
			LOG_INFO("monitor client disconnected: %s", conn->peerEp().address().to_string().c_str());
			break;
		}
	}
}
