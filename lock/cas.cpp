#include "timer.h"
#include <atomic>
#include <thread>

using namespace std;

atomic_int m;

void add() {
    for(int i = 0; i < 1000000; ++i) {
        m.fetch_add(1);
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
    cout << "count : " << m << endl;
    return 0;
}
