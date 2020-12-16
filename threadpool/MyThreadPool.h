#include <mutex>
#include "Task.h"
#include "MyThread.h"
#include "BusyThreadContainer.h"
#include "IdleThreadContainer.h"
#include "TaskContainer.h"

class MyThread;

class MyThreadPool{
public:
    MyThreadPool();
    MyThreadPool(int number);
    ~MyThreadPool();
    void AddTask(Task* task, int priority);
    void AddIdleThread(int n);
    void RemoveThreadFromBusy(MyThread* myThread);
    void Start();
    void EndMyThreadPool();

private:
    BusyThreadContainer busy_thread_container_;
    IdleThreadContainer idle_thread_container_;
    bool issurvive_;
    TaskContainer task_container_;
    std::thread thread_this_;
    std::mutex busy_mutex_;
    std::mutex idle_mutex_;
    std::mutex task_mutex_;
    int number_of_thread_;
};

