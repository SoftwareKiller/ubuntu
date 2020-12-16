#pragma once
#include <array>
#include <memory>
#include <asio.hpp>
#include <chrono>
#include <Buffer.h>
#include "Callbacks.h"
#include "Tcp_server.h"
#include "../base/AsyncLogging.h"

namespace net {
	class Session_Mgr;

	class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
	public:
		explicit TcpConnection(asio::io_context& io, Session_Mgr& session_mrg, const asio::ip::tcp::endpoint local);
		~TcpConnection();

		const asio::ip::tcp::endpoint& localEp() const { return local_; }
		const asio::ip::tcp::endpoint peerEp() const { return socket_.local_endpoint(); }

		bool connected() const { return state_ == kConnected; }
		void start();

		asio::ip::tcp::socket& fd() { return socket_; }

		void OnClose();

		void setId(uint64_t sid) {
			connection_id_ = sid;
		}

		void setMessageCallback(const MessageCallback& cb)
		{
			messageCallback_ = cb;
		}

		void setConnectionCallback(const ConnectionCallback& cb)
		{
			connectionCallback_ = cb;
		}

		void send(const string& message);

		void send(const char* data, size_t len);

		uint64_t getId() const {
			return connection_id_;
		}

	private:
		enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

		void do_read();
		void do_send();

		void setState(StateE s) { state_ = s; }

	private:
		StateE state_;
		uint64_t connection_id_;
		Session_Mgr& session_mrg_;
		asio::ip::tcp::socket socket_;
		asio::io_context& io_context_;
		asio::ip::tcp::endpoint local_;
		ConnectionCallback connectionCallback_;
		MessageCallback messageCallback_;
		WriteCompleteCallback writeCompleteCallback_;
		CloseCallback closeCallback;
		//std::array<char, 8192> inputBuffer_;
		Buffer inputBuffer_;
		Buffer outputBuffer_;
	};

	typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
}