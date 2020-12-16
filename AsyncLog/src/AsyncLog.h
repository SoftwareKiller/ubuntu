#pragma once

#include <cstdio>
#include <string>
#include <list>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <cstring>

#define LOG_API

enum LOG_LEVEL
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,    //用于业务错误
    LOG_LEVEL_SYSERROR, //用于技术框架本身的错误
    LOG_LEVEL_FATAL,    //FATAL 级别的日志会让在程序输出日志后退出
    LOG_LEVEL_CRITICAL  //CRITICAL 日志不受日志级别控制，总是输出
};

#define LOGT(...)    CAsyncLog::output(LOG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD(...)    CAsyncLog::output(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGI(...)    CAsyncLog::output(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...)    CAsyncLog::output(LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOGE(...)    CAsyncLog::output(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGSYSE(...) CAsyncLog::output(LOG_LEVEL_SYSERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGF(...)    CAsyncLog::output(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define LOGC(...)    CAsyncLog::output(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)

#define LOG_DEBUG_BIN(buf, buflength) CAsyncLog::outputBinary(buf, buflength)

class LOG_API CAsyncLog
{
public:
    static bool init(const char* pszLogFileName = nullptr, bool bTruncateLongLine = false, int64_t m_nFileRollSize = 10 * 1024 * 1024);
    static void uninit();

    static void setLevel(LOG_LEVEL nLevel);
    static bool isRunning();

    //不输出线程ID和函数签名、行号
    static bool output(long nLevel, const char* pszFmt, ...);
    //输出线程ID和函数签名、行号
    static bool output(long nLevel, const char* pszFileName, int nLineNo, const char* pszFmt, ...);

    static bool outputBinary(unsigned char* buffer, size_t);
private:
    CAsyncLog() = delete;
    ~CAsyncLog() = delete;

    CAsyncLog(const CAsyncLog& rhs) = delete;
    CAsyncLog& operator=(const CAsyncLog& rhs) = delete;

    static void makeLinePrefix(long nLevel, std::string& strPrefix);
    static void getTime(char* pszTime, int nTimeStrLength);
    static bool createNewFile(const char* pzsLogFileName);
    static bool writeToFile(const std::string& data);

    static void crash();

    static const char* ullto4Str(int n);
    static char* formLog(int& index, char* szbuf, size_t size_buf, unsigned char* buffer, size_t size);
    
    static void writeThreadProc();
private:
    static bool                          m_bToFile;                   //日志写入控制台还是文件
    static FILE*                         m_hLogFile;
    static std::string                   m_strFileName;
    static std::string                   m_strFileNamePID;            //文件名中的进程ID
    static bool                          m_bTruncateLongLog;          //长日志是否截断
    static LOG_LEVEL                     m_nCurrentLevel;
    static int64_t                       m_nFileRollSize;             //单个文件的最大字节数
    static int64_t                       m_nCurrentWrittenSize;       //已经写入的字节数目
    static std::list<std::string>        m_listLinesToWrite;          //待写入日志存储区
    static std::unique_ptr<std::thread>  m_spWriteThread;
    static std::mutex                    m_mutexWrite;
    static std::condition_variable       m_cvWrite;
    static bool                          m_bExit;
    static bool                          m_bRunning;
};

