#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<string.h>

int ticket = 100;
pthread_mutex_t mutex;

void* Buyticket(void* arg)
{
    char *id = (char*)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        if(ticket > 0)
        {
            usleep(1000);
            printf("%s, %d\n", id, ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }else{
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
}

int main()
{
    pthread_t tid1, tid2, tid3, tid4;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, Buyticket, "thread1");
    pthread_create(&tid2, NULL, Buyticket, "thread2");
    pthread_create(&tid3, NULL, Buyticket, "thread3");
    pthread_create(&tid4, NULL, Buyticket, "thread4");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

