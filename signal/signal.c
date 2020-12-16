#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_alrm(int s)
{
    //printf("signal:%d,兄弟，你弄不死我\n",s);
}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction new, old;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept = 0;
    new.sa_handler = sig_alrm;
    sigemptyset(&new.sa_mask);
    new.sa_flags = 0;
    sigaction(SIGALRM, &new, &old);
    //阻塞
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    alarm(nsecs);

    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);

    sigsuspend(&suspmask);

    unslept = alarm(0);
    sigaction(SIGALRM, &old, NULL);
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}

int main()
{
    mysleep(5);
    printf("5 seconds passed\n");


    //signal(2,hander);

    //alarm(5);

   // while(1)
   // {
   //     printf("I am a Running proggram\n");
   //     sleep(1);
   // }

    return 0;
}

