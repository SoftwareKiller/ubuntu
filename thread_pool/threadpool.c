#include<string.h>
#include<errno.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include"threadpool.h"

void *thread_routine(void *arg)
{
    struct timespec abstime;
    int timeout;
    printf("thread 0x%x is starting \n", (int)pthread_self());
    threadpool_t *pool = (threadpool_t*)arg;
    while(1)
    {
        timeout = 0;
        condition_lock(&pool->ready);
        pool->idle++;
        //等待队列中有任务到来或者线程池销毁通知
        while(pool->first == NULL && !pool->quit)
        {
            printf("thread 0x%x is waiting\n", (int)pthread_self());
            //condition_wait(&pool->ready);
            clock_gettime(CLOCK_REALTIME, &abstime);
            abstime.tv_sec += 1;
            int status = condition_timewait(&pool->ready,&abstime);
            if(status == ETIMEDOUT)
            {
                printf("thread 0x%x is wait time out\n",(int)pthread_self());
                timeout = 1;
                break;
            }
        }
        //等待到条件，处于工作状态
        pool->idle--;
        if(pool->first != NULL)
        {
            //从队头取出任务
            task_t *t = pool->first;
            pool->first = t->_next;
            //执行任务需要一定的时间，需要先解锁，以便生产者进程能够往队列中添加任务
            //其他消费者线程能够进入等待任务
            condition_unlock(&pool->ready);
            t->run(t->arg);
            free(t);
            condition_lock(&pool->ready);
        }
        //如果等待到线程池销毁通知，且任务都执行完毕
        if(pool->quit && pool->first == NULL)
        {
            pool->count--;
            if(pool->count == 0)
            {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            //跳出循环前记得解锁
            break;
        }

        if(timeout && pool->first == NULL)
        {
            pool->count--;
            condition_unlock(&pool->ready);
            break;
        }
        condition_unlock(&pool->ready);
    }

    printf("thread 0x%x is exting\n", (int)pthread_self());
    return NULL;
}

void threadpool_init(threadpool_t *pool, int threads)
{
    //对线程池中的各个字段初始化
    condition_init(&pool->ready);
    pool->first = NULL;
    pool->tail = NULL;
    pool->count = 0;
    pool->idle = 0;
    pool->max_threads = threads;
    pool->quit = 0;
}

void thread_add_task(threadpool_t *pool, void *(*run)(void *arg),void *arg)
{
    //生成新任务
    task_t *newtask = (task_t*)malloc(sizeof(task_t));
    if(newtask == NULL)
        exit(1);

    newtask->run = run;
    newtask->arg = arg;
    newtask->_next = NULL;

    condition_lock(&pool->ready);
    //将任务添加到队列
    if(pool->first == NULL)
        pool->first = newtask;
    else
        pool->tail->_next = newtask;
    pool->tail = newtask;

    //如果有等待线程则唤醒其中一个
    if(pool->idle > 0)
    {
        condition_signal(&pool->ready);
    }
    else if(pool->count < pool->max_threads)
    {
        //没有等待线程，并且当前线程数不超过最大线程数，则创建一个新线程
        pthread_t tid;
        pthread_create(&tid, NULL, thread_routine, pool);
        pool->count++;
    }

    condition_unlock(&pool->ready);
}

void threadpool_destroy(threadpool_t *pool)
{
    if(pool->quit)
    {
        return;
    }
    condition_lock(&pool->ready);
    pool->quit = 1;
    if(pool->count > 0)
    {
        if(pool->idle > 0)
            condition_broadcast(&pool->ready);

        //等待正在执行任务的线程
        while(pool->count > 0)
        {
            condition_wait(&pool->ready);
        }
    }
    condition_unlock(&pool->ready);
    condition_destroy(&pool->ready);
}
