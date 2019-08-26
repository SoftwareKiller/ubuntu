#pragma once 
#include <list>

class MyThread;

class BusyThreadContainer{
public:
    BusyThreadContainer();
    ~BusyThreadContainer();
    void push(MyThread* m);
    std::list<MyThread*>::size_type size();
    void erase(MyThread* m);
private:
    std::list<MyThread*> busy_thread_container_;
    typedef std::list<MyThread*> Container;
    typedef Container::iterator Iterator;
};

