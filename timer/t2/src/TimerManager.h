#ifndef _TIMERMANAGER_H_
#define _TIMERMANAGER_H_

#include <queue>
#include <memory>
#include <vector>
#include "Timer.h"

struct compareTimer{
    bool operator()(const std::shared_ptr<Timer> lhs, const std::shared_ptr<Timer> rhs) {
        return lhs->getExpiredTime() < rhs->getExpiredTime() ? true : false;
    }
};

class TimerManager{
public:
    TimerManager() = default;
    ~TimerManager() = default;

    int64_t addTimer(int64_t expired, int64_t interval, TimerCallBack cb);
    int64_t addTimer(int64_t expired, int64_t interval, int32_t repeat, TimerCallBack cb);
    bool removeTimer(int64_t id);

    void doTimer();

    int64_t nowTime();
private:
    std::priority_queue<std::shared_ptr<Timer>, std::vector<std::shared_ptr<Timer>> ,compareTimer> m_TimerQueue;
};

#endif

