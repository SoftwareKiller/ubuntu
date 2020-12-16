#include <chrono>
#include <functional>
#include <thread>
#include <iostream>

using namespace std;

typedef function<void()> Callback;

void print(){
    cout << "hello timer" << endl;
}

void call(int seconds, Callback cb) {
    this_thread::sleep_for(chrono::seconds(seconds));
    cb();
}

int main() {
    Callback cb;

    cb = print;

    int x = 3;
    while(x--) {
        call(2, cb);
    }

    return 0;
}

