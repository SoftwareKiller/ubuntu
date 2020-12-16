#pragma once
#include <condition_variable>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "asio.hpp"
#include "io_service_pool.h"
#include "Tcp_connection.h"
#include "Callbacks.h"
#include "session_mgr.h"

namespace net {
	enum ENUM_MSG_TYPE {
		MSG_TYPE_NONE = 0,			 //未知
		MSG_TYPE_EVENT = 1,			 //网络事件
		MSG_TYPE_CLIENT = 2,		 //客户端
		MSG_TYPE_CHAT_SERVER = 3,
		MSG_TYPE_COUNT,
	};

	class TcpServer {
	public:
		TcpServer(int port);
		virtual ~TcpServer();
		bool Initialize();
		void Stop();

		/*asio::io_context& GetAcceptIo() {
			return acceptor_->get_io_context();
		}*/

		bool Listen();
		void Accept();

		static IOContextPool& get_ioc_pool() {
			static IOContextPool instance(std::thread::hardware_concurrency());
			return instance;
		}


	public:
		//新连接过来时执行此回调
		void setConnecttionCallback(const ConnectionCallback& cb) {
			connectionCallback_ = cb;
		}

		void setMessageCallback(const MessageCallback& cb) {
			messageCallback_ = cb;
		}

		void setWriteCompleteCallback(const WriteCompleteCallback& cb) {
			writeCompleteCallback_ = cb;
		}

	private:
		//void newConnection(TcpConnectionPtr connection);
		std::shared_ptr<IdWorker> GetIdWorker() { return id_worker_; }

	private:
		ConnectionCallback              connectionCallback_;
		MessageCallback                 messageCallback_;
		WriteCompleteCallback           writeCompleteCallback_;

	private:
		//此服务器类型
		//ENUM_MSG_TYPE server_type_;

		const int hostport_;
		std::shared_ptr<IdWorker> id_worker_;
		Session_Mgr session_mgr_;

		std::unique_ptr<asio::ip::tcp::acceptor> acceptor_;
		static asio::io_context& acpt_io_() {
			static asio::io_context ios_;
			return ios_;
		}

		std::thread* acpt_io_thread_;
	};
}
