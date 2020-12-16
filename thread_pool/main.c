#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"threadpool.h"

void* mytask(void *arg)
{
    printf("thread 0x%x is working on task %d\n", (int)pthread_self(), *(int*)arg);
    free(arg);
    return NULL;
}

int main()
{
    threadpool_t pool;
    threadpool_init(&pool, 3);

    int i = 0;
    for(; i<1000000; ++i)
    {
        int *arg = (int*)malloc(sizeof(i));
        *arg = i;
        thread_add_task(&pool, mytask, arg);
    }
    //sleep(15);
    threadpool_destroy(&pool);
    return 0;
}

