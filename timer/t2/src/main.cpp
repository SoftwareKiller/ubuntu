#include <iostream>
#include <unistd.h>
#include "TimerManager.h"

using namespace std;

void print() {
    cout << "hello timer" << endl;
}

void p() {
    cout << "cp dd" << endl;
}

int main() {
    TimerManager mgr;

    TimerCallBack cb = print;

    cb = p;
    mgr.addTimer(mgr.nowTime() + 1000000, 1100000, cb);
    cb = print;
    mgr.addTimer(mgr.nowTime() + 1000000, 120000, 10, cb);
    mgr.addTimer(mgr.nowTime() + 100000, 2000000, 10, cb);

    int times = 0;
    while(++times < 11) {
        sleep(1);
        cout << times << " second after" << endl;
        mgr.doTimer();
    }

    return 0;
}

