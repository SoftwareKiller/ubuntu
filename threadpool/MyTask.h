#pragma once
#include "Task.h"

class MyTask:public Task{
    friend bool operator<(MyTask &lv, MyTask &rv) {
        return lv.priority_ < rv.priority_;
    }
public:
    MyTask();
    ~MyTask();
    virtual void Run();
    void setdata(int d);
private:
    int data_;
};

