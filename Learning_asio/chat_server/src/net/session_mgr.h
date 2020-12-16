#pragma once

#include <unordered_map>
#include "../utils/id_worker.h"
#include "../base/AsyncLogging.h"
#include "Callbacks.h"

namespace net {
	class Session_Mgr {
	public:
		Session_Mgr() = default;
		~Session_Mgr() = default;

		void AddSession(uint64_t session_id, TcpConnectionPtr connection);
		void DelSession(uint64_t session_id);

	private:
		std::unordered_map<uint64_t, TcpConnectionPtr> connect_mgr_;
		std::mutex mutex_;
	};
}
