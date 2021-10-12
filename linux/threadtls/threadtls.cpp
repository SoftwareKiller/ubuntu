#include <pthread.h>
#include <iostream>
#include <unistd.h>

//线程局部存储key
__thread int g_mydata = 99;

void* thread_functiona1(void* arg)
{
    while(true)
    {
        g_mydata++;
    }

    return NULL;
}

void* thread_functiona2(void* arg)
{
    while(true)
    {
        std::cout << "function2:" << g_mydata << "ThreadID:" << pthread_self() << std::endl;
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t threadID[2];
    pthread_create(&threadID[0], NULL, thread_functiona1, NULL);
    pthread_create(&threadID[1], NULL, thread_functiona2, NULL);

    for(int i = 0; i < 2; ++i)
        pthread_join(threadID[i], NULL);
    return 0;
}

