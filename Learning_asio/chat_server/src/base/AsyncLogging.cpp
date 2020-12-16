#include "AsyncLogging.h"
#include <ctime>
#include <sys/timeb.h>
#include <sstream>
#include <iostream>
#include <cstdarg>

#define MAX_LINE_LENGTH    256
#define DEFAULT_ROLL_SIZE  10 * 1024 * 1024

bool CAsyncLog::m_bTruncateLongLog = false;
FILE* CAsyncLog::m_hLogFile = nullptr;
std::string CAsyncLog::m_strFileName = "default";
//std::string CAsyncLog::m_strFileNamePID = "";
LOG_LEVEL CAsyncLog::m_nCurrentLevel = LOG_LEVEL_INFO;
int64_t CAsyncLog::m_nFileRollSize = DEFAULT_ROLL_SIZE;
int64_t CAsyncLog::m_nCurrentWrittenSize = 0;
std::list<std::string> CAsyncLog::m_listLinesToWrite;
std::unique_ptr<std::thread> CAsyncLog::m_spWriteThread;
std::mutex CAsyncLog::m_mutexWrite;
std::condition_variable CAsyncLog::m_cvWrite;
bool CAsyncLog::CAsyncLog::m_bExit = false;
bool CAsyncLog::m_bRunning = false;

bool CAsyncLog::init(const char* pszLogFileName/* = nullptr*/, bool bTruncateLongLine/* = false*/, int64_t nRollSize/* = 10*/)
{
    m_bTruncateLongLog = bTruncateLongLine;
    m_nFileRollSize = nRollSize;

    if (pszLogFileName == nullptr || pszLogFileName[0] == 0)
    {
        m_strFileName.clear();
    }
    else
        m_strFileName = pszLogFileName;

    //TODO:创建文件夹
    m_spWriteThread.reset(new std::thread(writeThreadProc));

    return true;
}

void CAsyncLog::uninit()
{
    m_bExit = true;

    m_cvWrite.notify_one();

    if (m_spWriteThread->joinable())
        m_spWriteThread->join();

    if (m_hLogFile != nullptr)
    {
        fclose(m_hLogFile);
        m_hLogFile = nullptr;
    }
}

void CAsyncLog::setLevel(LOG_LEVEL nLevel)
{
    if (nLevel < LOG_LEVEL_TRACE || nLevel > LOG_LEVEL_FATAL)
        return;
    m_nCurrentLevel = nLevel;
}

bool CAsyncLog::isRunning()
{
    return m_bRunning;
}

bool CAsyncLog::output(long nLevel, const char* pszFmt, ...)
{
    if (nLevel != LOG_LEVEL_CRITICAL)
    {
        if (nLevel < m_nCurrentLevel)
            return false;
    }

    //日志前缀
    std::string strLine;
    makeLinePrefix(nLevel, strLine);

    //日志正文
    std::string strLogMsg;

    va_list ap;
    va_start(ap, pszFmt);
    int nLogMsgLength = vsnprintf(NULL, 0, pszFmt, ap);
    va_end(ap);

    if ((int)strLogMsg.capacity() < nLogMsgLength + 1)
    {
        strLogMsg.resize(nLogMsgLength + 1);
    }

    va_list aq;
    va_start(aq, pszFmt);
    vsnprintf((char*)strLogMsg.data(), strLogMsg.capacity(), pszFmt, aq);
    va_end(aq);

    //string内容正确但length不对，恢复length
    std::string strMsgFormal;
    strMsgFormal.append(strLine.c_str(), nLogMsgLength);

    //如果开启日志截断，长日志只取MAX_LINE_LENGTH个字符
    if (m_bTruncateLongLog)
        strMsgFormal = strMsgFormal.substr(0, MAX_LINE_LENGTH);

    strLine += strMsgFormal;

    if (!m_strFileName.empty())
    {
        strLine += "\n";
    }

    if (nLevel != LOG_LEVEL_FATAL)
    {
        std::lock_guard<std::mutex> lock_guard(m_mutexWrite);
        m_listLinesToWrite.push_back(strLine);
        m_cvWrite.notify_one();
    }
    else
    {
        std::cout << strLine << std::endl;
        if (!m_strFileName.empty())
        {
            if (m_hLogFile == nullptr)
            {
                char szNow[64] = { 0 };
                time_t now = time(NULL);
                tm time;
#ifdef _WIN32
                localtime_s(&time, &now);
#else
                localtime_r(&now, &time);
#endif
                strftime(szNow, sizeof(szNow), "%Y%m%d%H%M%S", &time);
                std::string strNewFileName(m_strFileName);
                strNewFileName += ".";
                strNewFileName += szNow;
                strNewFileName += ".log";
                if (!createNewFile(strNewFileName.c_str()))
                    return false;
            }

            writeToFile(strLine);
        }

        crash();
    }

    return true;

}

bool CAsyncLog::output(long nLevel, const char* pszFileName, int nLineNo, const char* pszFmt, ...)
{
    if (nLevel != LOG_LEVEL_CRITICAL)
    {
        if (nLevel < m_nCurrentLevel)
            return false;
    }

    std::string strLine;
    makeLinePrefix(nLevel, strLine);

    //函数签名
    char szFileName[512] = { 0 };
    snprintf(szFileName, sizeof(szFileName), "[%s:%d]", pszFileName, nLineNo);
    strLine += szFileName;

    //日志正文
    std::string strLogMsg;

    va_list ap;
    va_start(ap, pszFmt);
    //会将pszFmt的长度返回，不包含\0
    int nLogMsgLength = vsnprintf(NULL, 0, pszFmt, ap);
    va_end(ap);

    if ((int)strLogMsg.capacity() < nLogMsgLength + 1)
    {
        strLogMsg.resize(nLogMsgLength + 1);
    }

    va_list aq;
    va_start(aq, pszFmt);
    vsnprintf((char*)strLogMsg.data(), strLogMsg.capacity(), pszFmt, aq);
    va_end(aq);

    std::string strMsgFormal;
    strMsgFormal.append(strLogMsg.c_str(), nLogMsgLength);

    if (m_bTruncateLongLog)
    {
        strMsgFormal = strMsgFormal.substr(0, MAX_LINE_LENGTH);
    }

    strLine += strMsgFormal;
    if (!m_strFileName.empty())
    {
        strLine += '\n';
    }

    if (nLevel != LOG_LEVEL_FATAL)
    {
        std::lock_guard<std::mutex> lock_guard(m_mutexWrite);
        m_listLinesToWrite.push_back(strLine);
        m_cvWrite.notify_one();
    }
    else
    {
        std::cout << strLine << std::endl;
        if (!m_strFileName.empty())
        {
            if (m_hLogFile == nullptr)
            {
                char szNow[64];
                time_t now = time(NULL);
                tm time;
#ifdef _WIN32
                localtime_s(&time, &now);
#else
                localtime_r(&now, &time);
#endif
                strftime(szNow, sizeof(szNow), "%Y%m%d%H%M%S", &time);

                std::string strNewFileName(m_strFileName);
                strNewFileName += ".";
                strNewFileName += szNow;
                strNewFileName += ".log";
                if (!createNewFile(strNewFileName.c_str()))
                    return false;
            }

            writeToFile(strLine);
        }

        crash();
    }

    return true;
}

bool CAsyncLog::outputBinary(unsigned char* buffer, size_t size)
{
    std::ostringstream os;

    static const size_t PRINTSIZE = 512;
    char szbuf[PRINTSIZE * 3 + 8];

    size_t lsize = 0;
    size_t lprintbufsize = 0;
    int index = 0;
    os << "address[" << (long)buffer << "] size[" << size << "] \n";
    while (true)
    {
        memset(szbuf, 0, sizeof(szbuf));
        if (size > lsize)
        {
            lprintbufsize = (size - lsize);
            lprintbufsize = lprintbufsize > PRINTSIZE ? PRINTSIZE : lprintbufsize;
            formLog(index, szbuf, sizeof(szbuf), buffer + lsize, lprintbufsize);
            size_t len = strlen(szbuf);

            os << szbuf;

            lsize += lprintbufsize;
        }
        else
        {
            break;
        }
    }

    std::lock_guard<std::mutex> lock_guard(m_mutexWrite);
    m_listLinesToWrite.push_back(os.str());
    m_cvWrite.notify_one();

    return true;
}

const char* CAsyncLog::ullto4Str(int n)
{
    static char buf[64 + 1];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%06u", n);
    return buf;
}

char* CAsyncLog::formLog(int& index, char* szbuf, size_t size_buf, unsigned char* buffer, size_t size)
{
    size_t len = 0;
    size_t lsize = 0;
    int headlen = 0;
    char szhead[64 + 1] = { 0 };
    char szchar[17] = "0123456789abcdef";
    while (size > lsize && len + 10 < size_buf)
    {
        if (lsize % 32 == 0)
        {
            if (0 != headlen)
            {
                szbuf[len++] = '\n';
            }

            memset(szhead, 0, sizeof(szhead));
            strncpy(szhead, ullto4Str(index++), sizeof(szhead) - 1);
            headlen = strlen(szhead);
            szhead[headlen++] = ' ';

            strcat(szbuf, szhead);
            len += headlen;
        }
        if (lsize % 16 == 0 && 0 != headlen)
        {
            szbuf[len++] = ' ';
        }
        szbuf[len++] = szchar[((buffer[lsize] >> 4) & 0xf)];
        szbuf[len++] = szchar[((buffer[lsize]) & 0xf)];
        lsize++;
    }
    szbuf[len++] = '\n';
    szbuf[len++] = '\0';
    return szbuf;
}

void CAsyncLog::makeLinePrefix(long nLevel, std::string& strPrefix)
{
    strPrefix = "[INFO]";
    if (nLevel == LOG_LEVEL_TRACE)
        strPrefix = "[TRACE]";
    else if (nLevel == LOG_LEVEL_DEBUG)
        strPrefix = "[DEBUG]";
    else if (nLevel == LOG_LEVEL_WARNING)
        strPrefix = "[WARN]";
    else if (nLevel == LOG_LEVEL_ERROR)
        strPrefix = "[ERROR]";
    else if (nLevel == LOG_LEVEL_SYSERROR)
        strPrefix = "[SYSE]";
    else if (nLevel == LOG_LEVEL_FATAL)
        strPrefix = "[FATAL]";
    else if (nLevel == LOG_LEVEL_CRITICAL)
        strPrefix = "[CRITICAL]";

    char szTime[64] = { 0 };
    getTime(szTime, sizeof(szTime));

    strPrefix += "[";
    strPrefix += szTime;
    strPrefix += "]";

    char szThreadID[32] = { 0 };
    std::ostringstream osThreadID;
    osThreadID << std::this_thread::get_id();
    snprintf(szThreadID, sizeof(szThreadID), "[%s]", osThreadID.str().c_str());
    strPrefix += szThreadID;
}

void CAsyncLog::getTime(char* pszTime, int nTimeStrLength)
{
    struct timeb tp;
    ftime(&tp);

    time_t now = tp.time;
    tm time;
#ifdef _WIN32
    localtime_s(&time, &now);
#else
    localtime_r(&now, &time);
#endif

    snprintf(pszTime, nTimeStrLength, "[%04d-%02d-%02d %02d:%02d:%02d:%03d]",
        time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour,
        time.tm_min, time.tm_sec, tp.millitm);
}

bool CAsyncLog::createNewFile(const char* pszLogFileName)
{
    if (m_hLogFile != nullptr)
        fclose(m_hLogFile);

    //始终新建新文件
    m_hLogFile = fopen(pszLogFileName, "w+");
    return m_hLogFile != nullptr;
}

bool CAsyncLog::writeToFile(const std::string& data)
{
    //为了防止长文件一次写不完，分批写入
    /*std:: string strLocal(data);
    int ret = 0;
    while(true)
    {
        ret = fwrite(strLocal.c_str(), 1, strLocal.length(), m_hLogFile);
        if( ret < 0 )
            return false;
        else if(ret <= (int)strLocal.length())
        {
            strLocal.erase(0, ret);
        }
        if(strLocal.empty())
            break;
    }*/

    int32_t written = 0;
    int32_t remain = data.length();
    while (remain > 0)
    {
        written = fwrite(data.c_str() + (data.length() - remain), 1, remain, m_hLogFile);
        if (written < 0)
            return false;
        else if (written <= remain)
        {
            remain -= written;
        }

        if (remain <= 0)
            break;
    }

    fflush(m_hLogFile);
    return true;
}

void CAsyncLog::crash()
{
    char* p = nullptr;
    *p = 0;
}

void CAsyncLog::writeThreadProc()
{
    m_bRunning = true;
    while (true)
    {
        if (!m_strFileName.empty())
        {
            if (m_hLogFile == nullptr || m_nCurrentWrittenSize >= m_nFileRollSize)
            {
                m_nCurrentWrittenSize = 0;

                char szNow[64];
                time_t now = time(NULL);
                tm time;
#ifdef _WIN32
                localtime_s(&time, &now);
#else
                localtime_r(&now, &time);
#endif
                strftime(szNow, sizeof(szNow), "%Y%m%d%H%M%S", &time);

                std::string strNewFileName(m_strFileName);
                strNewFileName += ".";
                strNewFileName += szNow;
                //strNewFileName += ".";
                //strNewFileName += m_strFileNamePID;
                strNewFileName += ".log";
                if (!createNewFile(strNewFileName.c_str()))
                    return;
            }
        }

        std::string strLine;
        {
            std::unique_lock<std::mutex> guard(m_mutexWrite);
            while (m_listLinesToWrite.empty())
            {
                if (m_bExit)
                    return;

                m_cvWrite.wait(guard);
            }

            strLine = m_listLinesToWrite.front();
            m_listLinesToWrite.pop_front();
        }

        //std::cout << strLine << std::endl;

        if (!m_strFileName.empty())
        {
            if (!writeToFile(strLine.c_str()))
                return;

            m_nCurrentWrittenSize += strLine.length();
        }
    }

    m_bRunning = false;
}
