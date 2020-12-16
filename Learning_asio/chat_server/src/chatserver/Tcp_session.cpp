#include "Tcp_session.h"
#include "../base/AsyncLogging.h"
#include "../base/Singleton.h"
#include "../net/ProtocolStream.h"
#include "../zlib1.2.11/ZlibUtil.h"
#include "chat_server.h"
#include "Msg.h"

TcpSession::TcpSession(const std::weak_ptr<TcpConnection>& conn) : tempConn_(conn) {

}

TcpSession::~TcpSession() {

}

void TcpSession::send(int32_t cmd, int32_t seq, const std::string& data) {
	send(cmd, seq, data.c_str(), data.length());
}

void TcpSession::send(int32_t cmd, int32_t seq, const char* data, int32_t len) {
	std::string outbuf;
	net::BinaryStreamWriter writeStream(&outbuf);
	writeStream.WriteInt32(cmd);
	writeStream.WriteInt32(seq);
	writeStream.WriteCString(data, len);
	writeStream.Flush();

    sendPackage(outbuf.c_str(), outbuf.length());
}

void TcpSession::sendPackage(const char* p, int32_t length)
{
    string srcbuf(p, length);
    string destbuf;
    if (!ZlibUtil::compressBuf(srcbuf, destbuf))
    {
        LOG_ERROR("compress buf error");
        return;
    }

    string strPackageData;
    chat_msg_header header;
    header.compressflag = 1;
    header.compresssize = destbuf.length();
    header.originsize = length;

    //插入一个包头
    strPackageData.append((const char*)&header, sizeof(header));
    strPackageData.append(destbuf);

    //TODO: 这些Session和connection对象的生命周期要好好梳理一下
    if (tempConn_.expired())
    {
        //FIXME: 出现这种问题需要排查
        LOG_ERROR("Tcp connection is destroyed , but why TcpSession is still alive ?");
        return;
    }

    std::shared_ptr<TcpConnection> conn = tempConn_.lock();
    if (conn)
    {
        conn->send(strPackageData);
    }
}
