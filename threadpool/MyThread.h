#pragma once

#include "Task.h"
#include <thread>
#include <algorithm>

class MyThreadPool;
class Task;

class MyThread{
    friend bool operator==(MyThread m1, MyThread m2);
    friend bool operator!=(MyThread m1, MyThread m2);
public:
    MyThread(MyThreadPool* pool);
    void Assign(Task* Task);
    void Run();
    void StartThread();
    int getthreadid();
    void setisdetach(bool isdetach);
private:
    MyThreadPool* mythreadpool_;
    static int s_threadnumber;
    bool isdetach_;
    Task* task_;
    int threadid_;
    std::thread thread_;
};

