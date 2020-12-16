#include "TimerManager.h"
#include <chrono>

int64_t TimerManager::addTimer(int64_t expired, int64_t interval, TimerCallBack cb) {
    auto sp = std::make_shared<Timer>(cb, expired, interval);
    m_TimerQueue.push(sp);
    return sp->getId();
}

int64_t TimerManager::addTimer(int64_t expired, int64_t interval, int32_t repeat, TimerCallBack cb) {
    auto sp = std::make_shared<Timer>(std::move(cb), expired, interval, repeat);
    m_TimerQueue.push(sp);
    return sp->getId();
}

bool TimerManager::removeTimer(int64_t id) {
    return true;
}

int64_t TimerManager::nowTime() {
    return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
}

void TimerManager::doTimer() {
    int64_t now = nowTime();

    while(!m_TimerQueue.empty() && m_TimerQueue.top()->getExpiredTime() < now) {
        auto timer = m_TimerQueue.top();
        timer->run();
        m_TimerQueue.pop();
        if(timer->getRepeat() == 0) {
            continue;
        }
        m_TimerQueue.push(timer);
    }
}

