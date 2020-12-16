#include "Tcp_server.h"
#include "../base/AsyncLogging.h"

using namespace net;

TcpServer::TcpServer(int port) 
	: acceptor_(new asio::ip::tcp::acceptor(acpt_io_()))
	, hostport_(port)
{
	//server_type_ = ENUM_MSG_TYPE::MSG_TYPE_COUNT;
}

TcpServer::~TcpServer() {
	if (acpt_io_thread_ != nullptr) {
		delete acpt_io_thread_;
		acpt_io_thread_ = nullptr;
	}
}

bool TcpServer::Initialize() {
	//server_type_ = server_type;

	if (!Listen())
		return false;

	id_worker_ = make_shared<IdWorker>(20000,1);
	acpt_io_thread_ = new std::thread([this] {acpt_io_().run(); });
	get_ioc_pool().Run();
	return true;
}

bool TcpServer::Listen() {
	asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), hostport_);
	acceptor_->open(ep.protocol());
	std::error_code ec;
	acceptor_->set_option(asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_->bind(ep, ec);
	if (ec) {
		LOG_ERROR("listen failed, msg:%s", ec.message().c_str());
		return false;
	}

	LOG_INFO("Start Listening at:%d", hostport_);
	//acceptor_->non_blocking();
	acceptor_->listen();
	Accept();

	return true;
}

void TcpServer::Accept() {
	LOG_INFO("Start Accept, acceptor blocking:%d", acceptor_->non_blocking());
	auto connection = make_shared<TcpConnection>(get_ioc_pool().get_io_context(), session_mgr_, acceptor_->local_endpoint());
	acceptor_->async_accept(connection->fd(), [connection, this](asio::error_code ec) {
		if (ec) {
			LOG_ERROR("accept error:%s", ec.message().c_str());
			acceptor_->close();
			return;
		}

		uint64_t sid = GetIdWorker()->CreateId();
		session_mgr_.AddSession(sid, connection);
		connection->setId(sid);

		LOG_INFO("New connect from, id is:%lld", sid);

		if (!messageCallback_)
			LOG_ERROR("message is null");
		connection->setConnectionCallback(connectionCallback_);
		//connection->setMessageCallback(messageCallback_);
		connection->start();
		Accept();
	});
}

void TcpServer::Stop() {
	acceptor_->close();

	if (acpt_io_thread_ != nullptr)
		acpt_io_thread_->join();

	get_ioc_pool().Stop();
	get_ioc_pool().Join();

	LOG_INFO("TcpServer stopped");
}
