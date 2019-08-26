#include "MyThread.h"
#include "MyThreadPool.h"
#include <iostream>

int MyThread::s_threadnumber = 0;

MyThread::MyThread(MyThreadPool* pool):
    mythreadpool_(pool),
    isdetach_(true)
{
    ++s_threadnumber;
    threadid_ = s_threadnumber;
}

void MyThread::setisdetach(bool detach) {
    isdetach_ = detach;
}

void MyThread::Assign(Task *t) {
    task_ = t;
}

void MyThread::Run() {
    std::cout << "Thread: " << threadid_ << " run ";
    task_->Run();
    mythreadpool_->RemoveThreadFromBusy(this);
}

int MyThread::getthreadid() {
    return threadid_;
}

void MyThread::StartThread() {
    thread_ = std::thread(&MyThread::Run, this);
    if(isdetach_)
        thread_.detach();
    else
        thread_.join();
}

bool operator==(MyThread m1, MyThread m2) {
    return m1.threadid_ == m2.threadid_;
}

bool operator!=(MyThread m1, MyThread m2) {
    return !(m1.threadid_ == m2.threadid_);
}

