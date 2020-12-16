#include "../net/Buffer.h"
#include "../net/TimerId.h"
#include "Tcp_session.h"

using namespace net;

struct OnlineUserInfo {
	int32_t        userid;
	std::string    username;
	std::string    nickname;
	std::string    password;
	int32_t        clienttype;
	int32_t        status;
};

class chat_session : public TcpSession{
public:
	chat_session(const std::shared_ptr<TcpConnection>& conn, int sessionid);
	virtual ~chat_session();

	chat_session(const chat_session& rhs) = delete;
	chat_session& operator =(const chat_session& rhs) = delete;

	void onRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp receivTime);

private:
	bool process(const std::shared_ptr<TcpConnection>& conn, const char* inbuf, size_t len);

	void onRegisterResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);

private:
	int32_t            m_id;
	OnlineUserInfo     m_userinfo;
	int32_t            m_seq;
	bool               m_isLogin;
	time_t             m_lastPackageTime;
	TimerId            m_checkOnlineTimerId;
};
