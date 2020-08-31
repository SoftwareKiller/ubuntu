/** 
 * 程序已守护进程方式运行
 * zhangyl 2018.08.20
 */
#ifndef WIN32
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
void daemon_run();
#endif
