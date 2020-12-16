#ifndef _TIMER_H_
#define _TIMER_H_

#include <cstdint>
#include <atomic>
#include <functional>

typedef std::function<void()> TimerCallBack;

class Timer{
public:
    Timer(const TimerCallBack& cb, int64_t when, int64_t interval, int32_t repeat = -1);
    Timer(const TimerCallBack&& cb, int64_t when, int64_t interval);
    ~Timer() = default;

public:
    int64_t getExpiredTime() const {
        return m_expired;
    }

    int64_t getInterval() const {
        return m_interval;
    }

    int32_t getRepeat() const {
        return m_repeat;
    }

    int64_t getId() {
        return m_id;
    }

    void run();
private:
    int64_t m_id;       //定时器ID
    int64_t m_expired;  //过期时间
    const int64_t  m_interval; //间隔时长
    int32_t m_repeat;   //重复次数
    const TimerCallBack m_callback;

    static std::atomic<int64_t> sequenced_;
};

#endif
