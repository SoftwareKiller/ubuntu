#include "MyThreadPool.h"
#include "MyTask.h"
#include <iostream>

using namespace std;

int main() {
    MyThreadPool mythreadPool(5);

    MyTask j[50];
    for(int i = 0; i < 50; ++i) {
        j[i].setdata(i);
    }
    for(int i = 0; i < 50; ++i) {
        mythreadPool.AddTask(&j[i], i);
    }
    int i = 0;
    while(true) {
        cin >> i;
        if(i == 100) {
            MyTask j;
            j.setdata(i);
            mythreadPool.AddTask(&j, i);
        }
        if(i == -1) {
            mythreadPool.EndMyThreadPool();
            break;
        }
    }
    return 0;
}

