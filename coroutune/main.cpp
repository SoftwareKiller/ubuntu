#include <unistd.h>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include "co_routine.h"

using namespace std;

queue<int> env;

void* producer(void* args){
    co_enable_hook_sys();
    stCoCond_t* cond = (stCoCond_t*)args;
    int id = 0;
    while(true) {
        printf("%s:%d produce id %d\n", __func__, __LINE__, id);
        env.push(id++);
        co_cond_signal(cond);
        poll(nullptr, 0, 500);
    }
}

void* consumer(void* args){
    co_enable_hook_sys();
    stCoCond_t* cond = (stCoCond_t*)args;
    while(true) {
        if(env.empty()) {
            co_cond_timedwait(cond, -1);
            continue;
        }
        int id = env.front();
        env.pop();
        printf("%s:%d consume id %d\n", __func__, __LINE__, id);
        co_cond_signal(cond);
        poll(nullptr, 0, 500);
    }
}

int main() {
    stCoCond_t* cond = co_cond_alloc();

    stCoRoutine_t* consumer_co;
    co_create(&consumer_co, nullptr, consumer, cond);
    co_resume(consumer_co);

    stCoRoutine_t* producer_co;
    co_create(&producer_co, nullptr, producer, cond);
    co_resume(producer_co);

    co_eventloop(co_get_epoll_ct(), nullptr, nullptr);
    return 0;
}
