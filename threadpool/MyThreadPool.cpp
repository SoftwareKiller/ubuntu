#include "MyThreadPool.h"
#include <iostream>

MyThreadPool::MyThreadPool(int number) {
    issurvive_ = true;
    number_of_thread_ = number;
    idle_thread_container_.assign(number, this);
    thread_this_ = std::thread(&MyThreadPool::Start, this);
    thread_this_.detach();
}

MyThreadPool::~MyThreadPool() {}

void MyThreadPool::EndMyThreadPool() {
    issurvive_ = false;
}

void MyThreadPool::AddIdleThread(int n) {
    idle_mutex_.lock();
    idle_thread_container_.assign(n, this);
    number_of_thread_ += n;
    idle_mutex_.unlock();
}

void MyThreadPool::Start() {
    while(true) {
        if(!issurvive_) {
            busy_mutex_.lock();
            if(busy_thread_container_.size()) {
                busy_mutex_.unlock();
                continue;
            }
            busy_mutex_.unlock();
            break;
        }
        idle_mutex_.lock();
        if(idle_thread_container_.size() == 0) {
            idle_mutex_.unlock();
            continue;
        }
        idle_mutex_.unlock();
        task_mutex_.lock();
        if(task_container_.size() == 0) {
            task_mutex_.unlock();
            continue;
        }
        Task* b = task_container_.top();
        task_container_.pop();
        task_mutex_.unlock();

        idle_mutex_.lock();
        MyThread* mythread = idle_thread_container_.top();
        idle_thread_container_.pop();
        mythread->Assign(b);
        idle_mutex_.unlock();

        busy_mutex_.lock();
        busy_thread_container_.push(mythread);
        busy_mutex_.unlock();
        mythread->StartThread();
    }
}

void MyThreadPool::AddTask(Task* task, int priority = (PRIORITY::NORMAL)) {
    task->SetPrioritt(priority);
    task_mutex_.lock();
    task_container_.push(task);
    task_mutex_.unlock();
}

void MyThreadPool::RemoveThreadFromBusy(MyThread* myThread) {
    busy_mutex_.lock();
    std::cout << "Thread: " << myThread->getthreadid() << "remove from busylist" << std::endl;
    busy_thread_container_.erase(myThread);
    busy_mutex_.unlock();

    idle_mutex_.lock();
    idle_thread_container_.push(myThread);
    idle_mutex_.unlock();
}

