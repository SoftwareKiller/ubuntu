#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

typedef struct node
{
    int data;
    struct node* _next;
}node,*pnode;

pnode head = NULL;

void pushfront(pnode* head, int data)
{
    pnode newnode = (pnode)malloc(sizeof(node));
    newnode->data = data;
    newnode->_next = NULL;
    if((*head) == NULL)
    {
        (*head) = newnode;
        printf("生产\n");
    }else{
        newnode->_next = (*head)->_next;
        (*head)->_next = newnode;
        printf("生产...\n");
    }
}

void popfront(pnode* head)
{
    if(*head == NULL)
    {
        printf("无物可消费\n");
        return;
    }else{
        pnode del = NULL;
        del = *head;
        (*head) = del->_next;
        free(del);
        del = NULL;
        printf("消费\n");
    }
}

void print(pnode head)
{
    while(head)
    {
        printf("%d ",head->data);
        head = head->_next;
    }
}

void destroy(pnode* head)
{
    pnode del = *head;
    while(del)
    {
        popfront(&del);
        del = del->_next;
    }

    *(head) = NULL;
}

void *prod()
{
    srand((unsigned)time(NULL));
    while(1)
    {
        int data = rand()%1024;
        pthread_mutex_lock(&mutex);
        pushfront(&head, data);
        printf("prod one data\n");
        print(head);
        printf("\n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        usleep(3000000);
    }
    return NULL;
}

void *cus(void* p)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(head == NULL)
        {
            printf("空仓\n");
            pthread_cond_wait(&cond, &mutex);
        }
        printf("可以拿取\n");
        popfront(&head);
        printf("cus one data\n");
        print(head);
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
    return NULL;
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_t cust, produ;
    pthread_create(&produ, NULL, prod, NULL);
    pthread_create(&cust, NULL, cus, NULL);

    void* ret;
    pthread_join(produ, &ret);
    free(ret);
    pthread_join(cust, &ret);
    destroy(&head);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
