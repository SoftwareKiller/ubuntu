#include "Timer.h"

std::atomic<int64_t> Timer::sequenced_;

Timer::Timer(const TimerCallBack&& cb, int64_t when, int64_t interval)
    :m_callback(cb)
    ,m_id(sequenced_++)
    ,m_expired(when)
    ,m_interval(interval)
{
}

Timer::Timer(const TimerCallBack& cb, int64_t when, int64_t interval, int32_t repeat)
    :m_callback(cb)
    ,m_id(sequenced_++)
    ,m_expired(when)
    ,m_interval(interval)
    ,m_repeat(repeat)
{
}

void Timer::run() {
    m_callback();
    if(m_repeat != -1) {
        if(m_repeat == 0)
            return;
        --m_repeat;
    }

    m_expired += m_interval;
}

