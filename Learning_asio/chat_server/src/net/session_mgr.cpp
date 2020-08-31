#include "session_mgr.h"

using namespace net;

void Session_Mgr::AddSession(uint64_t session_id, TcpConnectionPtr connection) {
	std::unique_lock<std::mutex> lock(mutex_);
	connect_mgr_[session_id] = connection;
}

void Session_Mgr::DelSession(uint64_t session_id) {
	std::unique_lock<std::mutex> lock(mutex_);
	auto session = connect_mgr_.find(session_id);

	if (session == connect_mgr_.end()) {
		LOG_ERROR("DelSession Error, session id is:%lld", session_id);
		return;
	}

	LOG_INFO("Delete Session, Session id is:%lld", session_id);
	connect_mgr_.erase(session);
}