#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include "../utils/DaemonRun.h"
#include "mysql.h"
#endif
#include <cstdlib>

#include <chrono>
#include <iostream>

#include "../base/AsyncLogging.h"
#include "../base/ConfigFileReader.h"
#include "../net/EventLoop.h"
#include "../chatserver/HttpServer.h"
#include "../chatserver/chat_server.h"
#include "../base//Singleton.h"
#include "../mysqlmgr/MysqlManager.h"
#include "UserManager.h"

net::EventLoop ep;

#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD CtrlType) {
	switch (CtrlType) {
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		ep.quit();
		break;

	default:
		break;
	}

	return TRUE;
}
#else
void prog_exit(int signo)
{
	std::cout << "program recv signal [" << signo << "] to exit." << std::endl;

	//Singleton<MonitorServer>::Instance().uninit();
	Singleton<HttpServer>::Instance().uninit();
	Singleton<ChatServer>::Instance().uninit();
	//g_mainLoop.quit();

	CAsyncLog::uninit();
}
#endif

int main(int argc, char* argv[])
{
#ifdef _WIN32
	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), false), SC_CLOSE, MF_GRAYED | MF_BYCOMMAND);
#else
	//设置信号处理
	signal(SIGCHLD, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, prog_exit);
	signal(SIGTERM, prog_exit);


	int ch;
	bool bdaemon = false;
	while ((ch = getopt(argc, argv, "d")) != -1)
	{
		switch (ch)
		{
		case 'd':
			bdaemon = true;
			break;
		}
	}

	if (bdaemon)
		daemon_run();
#endif

#ifdef WIN32
	CConfigFileReader config("../etc/chatserver.conf");
#else
	CConfigFileReader config("etc/chatserver.conf");
#endif
	std::string logFileFullPath;
	const char* logfilepath = config.GetConfigName("logfiledir");
    if(logfilepath == nullptr) {
        LOG_FATAL("logdir is not set in config file");
        return 1;
    }
	const char* logfilename = config.GetConfigName("logfilename");

#ifndef _WIN32
    DIR* dp = opendir(logfilepath);
    if(dp == nullptr) {
        if(mkdir(logfilepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            LOG_FATAL("create base dir errir, %s, errno: %d, %s", logfilepath, errno, strerror(errno));
            return 1;
        }
    }
    closedir(dp);
#endif

	logFileFullPath = logfilepath;
	logFileFullPath += logfilename;

	CAsyncLog::init(logFileFullPath.c_str());
	LOG_INFO("%s", logFileFullPath.c_str());
	LOG_INFO("+++++++++++++++++++++++++++++++++++++++++++++++");
	LOG_INFO("+                   Chat Start                +");
	LOG_INFO("+++++++++++++++++++++++++++++++++++++++++++++++");

	//初始化数据库配置
	const char* dbserver = config.GetConfigName("dbserver");
	const char* dbuser = config.GetConfigName("dbuser");
	const char* dbpassword = config.GetConfigName("dbpassword");
	const char* dbname = config.GetConfigName("dbname");

    CMysqlManager handle;
	//if (!Singleton<CMysqlManager>::Instance().init(dbserver, dbuser, dbpassword, dbname)) {
    if(!handle.init(dbserver, dbuser, dbpassword, dbname)) {
		LOG_FATAL("Init mysql failed, please check your database config.");
	}
	else {
		LOG_INFO("Init mysql success");
	}

	if (!Singleton<UserManager>::Instance().init(dbserver, dbuser, dbpassword, dbname))
	{
		LOG_FATAL("Init UserManager failed, please check your database config..............");
	}
    

	Singleton<ChatServer>::Instance().init(20000);
	Singleton<HttpServer>::Instance().init(8888);


	ep.loop();

	CAsyncLog::uninit();
}
