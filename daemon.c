#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

void mydaemon()
{
    int i;
    int fd0;
    pid_t pid;
    struct sigaction sa;

    umask(0);
    if((pid = fork()) < 0)
    {
        perror("fork");
    }else if(pid > 0){
        exit(0);
    }
    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGCHLD, &sa, NULL) < 0){
        return;
    }

    if((pid = fork()) < 0){
        perror("fork");
        return;
    }else if(pid != 0){
        exit(0);
    }

    if(chdir("/") < 0){
        perror("chdir");
        return;
    }
    close(0);
    fd0 = open("/dev/null",O_RDWR);
    dup2(fd0, 1);
    dup2(fd0, 2);
}

void deamon_run() {
    int pid;
    signal(SIGCHLD, SIG_IGN);

    pid = fork();
    if(pid < 0) {
        perror("fork error\n");
        exit(-1);
    }
    else if(pid > 0) {
        exit(0);
    }

    setsid();

    int fd;
    fd = open("/dev/null", O_RDWR, 0);
    if(fd != -1)
    {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    }

    if(fd > 2)
        close(fd);
}

int main()
{
    mydaemon();
    while(1){
        sleep(1);
    }
    return 0;
}

