#pragma once
#include <queue>

class Task;
class TaskContainer {
public:
    TaskContainer();
    ~TaskContainer();
    void push(Task*);
    Task* top();
    void pop();
    std::priority_queue<Task*>::size_type size();
private:
    std::priority_queue<Task*> task_container_;
};

