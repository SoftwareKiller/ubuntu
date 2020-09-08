#include"BussinessLogic.h"
#include <string>
#include "../base/Singleton.h"
#include "../utils/json.hpp"
#include "UserManager.h"

void BussinessLogic::registerUser(const std::string& data, const std::shared_ptr<TcpConnection>& conn, bool keeplive, std::string& retData) {
	using json_t = nlohmann::json;

	auto jsonData = json_t::parse(data);

	LOG_INFO("username:%s, nicename:%s, password:%s", jsonData["username"], jsonData["nickname"], jsonData["password"]);
	
	User u;
	u.username = jsonData["username"].get<std::string>();
	u.nickname = jsonData["nickname"].get<std::string>();
	u.password = jsonData["password"].get<std::string>();

	User cachedUser;
	cachedUser.userid = 0;
	Singleton<UserManager>::Instance().getUserInfoByUsername(u.username, cachedUser);
	if (cachedUser.userid != 0)
		retData = "{\"code\": 101, \"msg\": \"registered already\"}";
	else
	{
		if (!Singleton<UserManager>::Instance().addUser(u))
			retData = "{\"code\": 100, \"msg\": \"register failed\"}";
		else
		{
			retData = "{\"code\": 0, \"msg\": \"ok\"}";
		}
	}
}
