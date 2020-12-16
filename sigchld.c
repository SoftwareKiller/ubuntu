#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void handler(int sig)
{
    pid_t id;
    while( (id = waitpid(-1, NULL, WNOHANG)) > 0 ){
        printf("wait child success:%d\n",id);
    }
    printf("child is quit! %d\n",getpid());
}

int main()
{
    signal(SIGCHLD, handler);

    pid_t id;
    if((id = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if(id == 0){
        printf("child :%d\n", getpid());
        sleep(2);
        exit(1);
    }

    while(1)
    {
        printf("father still running\n");
        sleep(1);
    }

    return 0;
}
