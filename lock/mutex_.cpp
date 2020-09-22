#include "timer.h"
#include <thread>
#include <mutex>

using namespace std;

mutex m;
int count = 0;

void add() {
    for(int i = 0; i < 1000000; ++i)
    {
        lock_guard<mutex> lock(m);
        ++count;
    }
}

int main() {
    timer t;
    thread* th[10];
    for(int i = 0; i < 10; ++i) {
        th[i] = new thread(add);
    }

    for(int i = 0; i < 10; ++i) {
        th[i]->join();
        delete th[i];
    }
    cout << "count : " << count << endl;
    return 0;
}
