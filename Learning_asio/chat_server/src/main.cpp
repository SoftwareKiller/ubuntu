#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#endif
#include <cstdlib>

#include <chrono>
#include <iostream>

#include "../base/AsyncLogging.h"
#include "../base/ConfigFileReader.h"
#include "../net/Tcp_server.h"
#include "../net/EventLoop.h"
#include "../chatserver/HttpServer.h"
#include "../utils/DaemonRun.h"
#include "base/Singleton.h"

#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD CtrlType) {
	switch (CtrlType) {
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
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
	//Singleton<ChatServer>::Instance().uninit();
	//g_mainLoop.quit();

	CAsyncLog::uninit();
}
#endif

int main(int argc, char* argv[])
{
	//CAsyncLog::init("D:\\workplace\\chatserver\\build\\src\\Debug\\log\\log");
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

#ifndef _WIN32
    if (logfilepath == NULL)
    {
        LOG_FATAL("logdir is not set in config file");
        return 1;
    }

    //如果log目录不存在则创建之
    DIR* dp = opendir(logfilepath);
    if (dp == NULL)
    {
        if (mkdir(logfilepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
        {
            LOG_FATAL("create base dir error, %s , errno: %d, %s", logfilepath, errno, strerror(errno));
            return 1;
        }
    }
    closedir(dp);

    logFileFullPath = logfilepath;
#endif
	logFileFullPath = logfilepath;
	const char* logfilename = config.GetConfigName("logfilename");
	logFileFullPath += logfilename;

	CAsyncLog::init(logFileFullPath.c_str());

	LOG_INFO("%s", logFileFullPath.c_str());
	LOG_INFO("+++++++++++++++++++++++++++++++++++++++++++++++");
	LOG_INFO("+                   Chat Start                +");
	LOG_INFO("+++++++++++++++++++++++++++++++++++++++++++++++");

    Singleton<HttpServer>::Instance().init(20000);
	
	net::EventLoop ep;

	ep.loop();

	CAsyncLog::uninit();
}
