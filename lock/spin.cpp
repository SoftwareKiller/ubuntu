#include <atomic>
#include <thread>
#include "timer.h"

using namespace std;

class SpinLock final
{
public:
    using this_type   = SpinLock;
    using atomic_type = std::atomic_flag;

public:
    SpinLock() = default;
    ~SpinLock() = default;

    SpinLock(const this_type&) = delete;
    SpinLock& operator=(const this_type&) = delete;
public:
    void lock() noexcept
    {
        for(;;) {
            if (!m_lock.test_and_set()) {
                return;

            }

            std::this_thread::yield();

        }

    }

    bool try_lock() noexcept
    {
        return !m_lock.test_and_set();

    }

    void unlock() noexcept
    {
        m_lock.clear();

    }
private:
    atomic_type m_lock {false};

};

// RAII for lock
class SpinLockGuard final
{
public:
    using this_type      = SpinLockGuard;
    using spin_lock_type = SpinLock;
public:
    SpinLockGuard(spin_lock_type& lock) noexcept
        : m_lock(lock)
        {
            m_lock.lock();
        }

    ~SpinLockGuard() noexcept
    {
        m_lock.unlock();
    }

public:
    SpinLockGuard(const this_type&) = delete;
    SpinLockGuard& operator=(const this_type&) = delete;
private:
    spin_lock_type& m_lock;
};

SpinLock sp;
int count = 0;

void add(){
    for(int i = 0; i < 1000000; ++i){
        //SpinLockGuard lock(sp);
        sp.lock();
        ++count;
        sp.unlock();
    }

}

int main() {
    timer t;
    thread* th[10];
    for(int i = 0; i < 10; ++i) {
        th[i] = new thread(add);

    }

    for(int i = 0; i < 10; ++i) {
        th[i]->join();
        delete th[i];

    }
    cout << "count : " << count << endl;
    return 0;

}
