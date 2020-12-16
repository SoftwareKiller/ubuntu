#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
#include <stack>
#include "co_hook_sys_call.cpp"
#include "co_routine_inner.h"

using namespace std;

struct task_t{
    stCoRoutine_t* co;
    int fd;
};

stack<task_t*> g_readwrite;
int listen_fd = -1;

int Start(const char* ip, int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        cerr << "socket error" << endl;
        terminate();
    }

    if(port != 0) {
        int reuse = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

        struct sockaddr_in client;
        client.sin_family = AF_INET;
        client.sin_addr.s_addr = inet_addr(ip);
        client.sin_port = htons(port);
        int ret = bind(fd, (struct sockaddr*)&client, sizeof(client));
        if(ret != 0) {
            close(fd);
            cerr << "bind error" << endl;
            terminate();
        }
    }

    return fd;
}

int SetNonBlock(int fd) {
    int flag = fcntl(fd, F_GETFL, 0);
    flag |= O_NONBLOCK;
    flag |= O_NDELAY;
    int ret = fcntl(fd, F_SETFL, flag);
    return ret;
}

void *readwrite_routine(void* arg) {
    //hook curr coroutine
    co_enable_hook_sys();

    task_t* co = (task_t*)arg;
    char buf[1024 * 16];
    for(;;) {
        if(-1 == co->fd) {
            g_readwrite.push(co);
            co_yield_ct();
            continue;
        }

        int fd = co->fd;
        co->fd = -1;

        for(;;) {
            struct pollfd pf = {0};
            pf.fd = fd;
            pf.events = (POLLIN|POLLERR|POLLHUP);
            co_poll( co_get_epoll_ct(), &pf, 1, 1000 );

            int ret = read(fd, buf, sizeof(buf));
            if(ret > 0) {
                ret = write(fd, buf, sizeof(buf));
            }
            if(ret > 0 || (-1 == ret && EAGAIN == errno))
                continue;
            close(fd);
            break;
        }
    }
}

void* accept_routine(void*) {
    co_enable_hook_sys();
    cout << "accept corotine" << endl;
    for(;;) {
        if(g_readwrite.empty()) {
            cout << "empty" << endl;
            struct pollfd pf = {0};
            pf.fd = -1;
            poll(&pf, 1, 1000);
            continue;
        }

        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        socklen_t len = sizeof(server);

        int fd = co_accept(listen_fd, (struct sockaddr*)&server, &len);
        if(fd < 0) {
            struct pollfd pf = {0};
            pf.fd = listen_fd;
            pf.events =  (POLLIN|POLLERR|POLLHUP);
            co_poll(co_get_epoll_ct(), &pf, 1, 1000);
            continue;
        }
        if(g_readwrite.empty()) {
            close(fd);
            continue;
        }
        SetNonBlock(fd);
        task_t* co = g_readwrite.top();
        co->fd = fd;
        g_readwrite.pop();
        co_resume(co->co);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage :[ip], [port]" << endl;
        return -1;
    }

    const char* ip = argv[1];
    int port = stoi(argv[2]);

    listen_fd = Start(ip, port);
    if(listen(listen_fd, 1024) < 0) {
        cerr << "listen error" << endl;
        return -1;
    }

    cout << "listen " << listen_fd << " " << ip << " " << port << endl;
    SetNonBlock(listen_fd);

    for(int i = 0; i < 1024; ++i) {
        task_t* task = (task_t*)malloc(sizeof(task_t));
        task->fd = -1;

        co_create(&task->co, nullptr, readwrite_routine, task);
        co_resume(task->co);
    }

    stCoRoutine_t *accept_co = nullptr;
    co_create(&accept_co, nullptr, accept_routine, 0);
    co_resume(accept_co);

    co_eventloop(co_get_epoll_ct(), 0, 0);

    return 0;
}

