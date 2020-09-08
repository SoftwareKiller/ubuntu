#include "MysqlThrd.h"
#include <functional>
#include "../base/AsyncLogging.h"

CMysqlThrd::CMysqlThrd(void) {
	m_bTerminate = false;
	m_bStart = false;
	m_poConn = nullptr;
}

CMysqlThrd::~CMysqlThrd(void) {
}

void CMysqlThrd::Run() {
	mainLoop();
	uninit();

	if (nullptr != m_pThread) {
		m_pThread->join();
	}
}

bool CMysqlThrd::start(const std::string& host, const std::string& user, const std::string& pwd, const std::string& dbname) {
	m_poConn = new CDatabaseMysql();

	if (nullptr == m_poConn) {
		LOG_FATAL("CMysqlThrd::start, Cannot open database");
		return false;
	}

	if (m_poConn->initialize(host, user, pwd, dbname) == false) {
		return false;
	}

	return init();
}

void CMysqlThrd::stop() {
	if (m_bTerminate) {
		return;
	}
	m_bTerminate = true;
	m_pThread->join();
}

bool CMysqlThrd::init() {
	if (m_bStart) {
		return true;
	}

	m_pThread.reset(new std::thread(std::bind(&CMysqlThrd::mainLoop, this)));

	{
		std::unique_lock<std::mutex> lock(mutex_);
		while (m_bStart == false) {
			cond_.wait(lock);
		}
	}
}

void CMysqlThrd::uninit() {
}

void CMysqlThrd::mainLoop() {
	m_bStart = true;

	{
		std::unique_lock<std::mutex> guard(mutex_);
		cond_.notify_all();
	}

	IMysqlTask* poTask;
	while (!m_bTerminate) {
		if (nullptr != (poTask = m_oTask.pop())) {
			poTask->execute(m_poConn);
			m_oReplyTask.push(poTask);
			continue;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}
}
