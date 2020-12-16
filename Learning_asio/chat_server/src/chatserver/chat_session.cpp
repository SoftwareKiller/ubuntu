#include "chat_session.h"
#include <cstring>
#include <sstream>
#include <list>
#include "../net/Tcp_connection.h"
#include "../base/AsyncLogging.h"
#include "../net/ProtocolStream.h"
#include "Msg.h"
#include "../zlib1.2.11/ZlibUtil.h"
#include "BussinessLogic.h"

#define MAX_PACKAGE_SIZE 10 * 1024 * 1024

using namespace std;
using namespace net;

chat_session::chat_session(const std::shared_ptr<TcpConnection>& conn, int sessionid)
	:TcpSession(conn)
	, m_id(sessionid)
	, m_seq(0)
	, m_isLogin(false)
{
	m_userinfo.userid = 0;
	m_lastPackageTime = time(nullptr);
}

chat_session::~chat_session() {
	std::shared_ptr<TcpConnection> conn = getConnectionPtr();
	if (conn) {
		LOG_INFO("Remove chat session");
		conn->OnClose();
	}
}

void chat_session::onRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp recvieTime) {
	while (true) {
		if (pBuffer->readableBytes() < (size_t)sizeof(chat_msg_header))
			return;

		chat_msg_header header;
		memcpy(&header, pBuffer->peek(), sizeof(chat_msg_header));

		if (header.compressflag == PACKAGE_COMPRESSED) {
			//包头有错误，立即关闭连接
			if (header.compresssize <= 0 || header.compresssize > MAX_PACKAGE_SIZE ||
				header.originsize <= 0 || header.originsize > MAX_PACKAGE_SIZE)
			{
				//客户端发非法数据包，服务器主动关闭之
				LOG_ERROR("Illegal package, compresssize: %lld, originsize: %lld, close TcpConnection, client: %s", header.compresssize, header.originsize, conn->peerEp().address().to_string().c_str());
				conn->OnClose();
				return;
			}

			//收到的数据不够一个完整的包
			if (pBuffer->readableBytes() < (size_t)header.compresssize + sizeof(chat_msg_header))
				return;

			pBuffer->retrieve(sizeof(chat_msg_header));
			std::string inbuf;
			inbuf.append(pBuffer->peek(), header.compresssize);
			pBuffer->retrieve(header.compresssize);
			std::string destbuf;
			if (!ZlibUtil::uncompressBuf(inbuf, destbuf, header.originsize)) {
				LOG_ERROR("uncompress error, client:%s", conn->peerEp().address().to_string().c_str());
				conn->OnClose();
				return;
			}

			if (!process(conn, destbuf.c_str(), destbuf.length())) {
				LOG_ERROR("Process error, close TcpConnection, client: :%s", conn->peerEp().address().to_string().c_str());
				conn->OnClose();
				return;
			}
		}
	}
}

bool chat_session::process(const std::shared_ptr<TcpConnection>& conn,const char* inbuf, size_t len) {
	BinaryStreamReader readStream(inbuf, len);
	int32_t cmd;
	if (!readStream.ReadInt32(cmd)) {
		LOG_ERROR("read cmd error, client: %s", conn->peerEp().address().to_string().c_str());
		return false;
	}

	if (!readStream.ReadInt32(m_seq)) {
		LOG_ERROR("read seq error, client: %s", conn->peerEp().address().to_string().c_str());
		return false;
	}

	std::string data;
	size_t datalength;
	if (!readStream.ReadString(&data, 0, datalength))
	{
		LOG_ERROR("read data error, client: %s", conn->peerEp().address().to_string().c_str());
		return false;
	}

	switch (cmd)
	{
	case msg_type_register:
		onRegisterResponse(data, conn);
		break;
	default:
		break;
	}

	return true;
}

void chat_session::onRegisterResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn) {
	string retData;

	BussinessLogic::registerUser(data, conn, true, retData);
	if (!retData.empty()) {
		send(msg_type_register, m_seq, retData);

		LOG_INFO("Response to client: cmd=msg_type_register, data: %s. client: %s", retData.c_str(), conn->peerEp().address().to_string().c_str());
	}
}
