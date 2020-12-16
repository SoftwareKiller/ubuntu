#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include"condition.h"

//任务结构体，将任务放入队列由线程池来执行
typedef struct task
{
    void *(*run)(void *arg);    //任务回调函数
    void *arg;                  //回调函数参数
    struct task *_next;
}task_t;

//线程池结构体
typedef struct threadpool
{
    condition_t ready;
    task_t *first;
    task_t *tail;
    int count;
    int idle;
    int max_threads;
    int quit;
}threadpool_t;

//初始化线程池
void threadpool_init(threadpool_t* pool, int threads);

//往线程池中添加任务
void thread_add_task(threadpool_t *pool, void *(*run)(void *arg),void *arg);

//销毁线程池
void threadpool_destroy(threadpool_t *pool);

#endif
