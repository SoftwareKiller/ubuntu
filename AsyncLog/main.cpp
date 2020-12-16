#include <chrono>
#include <iostream>
#include "src/AsyncLog.h"

using namespace std;

int main()
{
	CAsyncLog::init("./test");
	chrono::time_point<chrono::system_clock, chrono::microseconds> now = chrono::time_point_cast<chrono::microseconds>(
		chrono::system_clock::now());
    unsigned long long start = now.time_since_epoch().count();
	for (int i = 0; i < 120000; ++i)
	{
		LOGI("Today is April 9, num i is %d", i);
	}

	now = chrono::time_point_cast<chrono::microseconds>(
		chrono::system_clock::now());
    unsigned long long end = now.time_since_epoch().count();

    LOGI("TIME:%llu", end - start);
    CAsyncLog::uninit();
}

