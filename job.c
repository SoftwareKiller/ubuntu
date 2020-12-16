#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        while(1)
        {
            printf("child(%d):I am a running process!!!\n",getpid());
            sleep(1);
        }
    }else{
        int i = 5;
        while(i--)
        {
            printf("parent(%d)# I am father!!!\n",getpid());
            sleep(1);
        }
    }
    return 0;
}
