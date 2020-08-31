#include "http_session.h"
#include <sstream>
#include <string.h>
#include <vector>
#include "StringUtil.h"

#define MAX_URL_LENGTH 2048

http_session::http_session(std::shared_ptr<TcpConnection>& conn) : m_tempConn(conn)
{
}

void http_session::onRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp receivTime) {
	LOG_INFO("Read message on http session");

	string inbuf;

	inbuf.append(pBuffer->peek(), pBuffer->readableBytes());

	if (inbuf.length() <= 4)
		return;

	string end = inbuf.substr(inbuf.length() - 4);
	if (end != "\r\n\r\n")
		return;
	else if (inbuf.length() >= MAX_URL_LENGTH)
	{
		conn->OnClose();
		return;
	}

	std::vector<string> lines;
	StringUtil::split(inbuf, lines, "\r\n");
	if (lines.size() < 1 || lines[0].empty()) {
		conn->OnClose();
		return;
	}

	std::vector<string> chunk;
	StringUtil::split(lines[0], chunk, " ");
	if (chunk.size() < 3) {
		conn->OnClose();
		return;
	}

	LOG_INFO("url: %s from %s:%d", chunk[1].c_str(), conn->peerEp().address().to_string().c_str(), conn->peerEp().port());

	std::vector<string> part;
	StringUtil::split(chunk[1], part, "?");

	//if (part.size() < 2) {
	//	conn->OnClose();
	//	return;
	//}

	string url = part[0];
	string param;// = part[1].substr(2);

	if (!process(conn, url, param))
		LOG_ERROR("handle http request error, from: %s, request: %s", conn->peerEp().address().to_string().c_str(), pBuffer->retrieveAllAsString().c_str());

	conn->OnClose();
}

bool http_session::process(const std::shared_ptr<TcpConnection>& conn, const std::string& url, const std::string& param) {
	if (url.empty())
		return false;

	if (url == "/") {
		string response = "HTTP/1.1 200 OK\r\n\r\n<html><h1>chat_server,start</h1></html>";
		conn->send(response);
		return true;
	}

	return false;
}
