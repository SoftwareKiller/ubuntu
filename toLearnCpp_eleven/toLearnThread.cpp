#include <list>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <ctime>
#include <unistd.h>

struct Data
{
	std::condition_variable m_cond;
	std::mutex m_mutex;
	std::list<int> m_data;

	void print() {
		for (auto& iter : m_data)
			std::cout << iter << " ";
		std::cout << std::endl;
	}
};

class custom
{
public:
	void cus(Data& data) {
		while (1) {
			{
				if (data.m_data.empty()) {
					std::unique_lock<std::mutex> lock(data.m_mutex);
					std::cout << "空仓" << std::endl;
					data.m_cond.wait(lock);
				}
				{
					std::unique_lock<std::mutex> lock(data.m_mutex);
					std::cout << "消费:" << data.m_data.front() << std::endl;
					data.m_data.pop_front();
				}
				sleep(1);
			}
			data.print();
		}
	}
};

class prod {
public:
	void product(Data& data) {
		srand((unsigned)time(NULL));
		while (1)
		{
			int num = rand() % 1024;
			{
				std::unique_lock<std::mutex> lock(data.m_mutex);
				data.m_data.push_back(num);
				std::cout << "生产一个数据:" << num << std::endl;
				data.print();
				data.m_cond.notify_all();
			}
			sleep(1);
		}
	}
};

int main() {
	Data num;
	std::thread t1(&prod::product, prod(), std::ref(num));
	std::thread t2(&custom::cus, custom(), std::ref(num));
	t2.join();
	t1.join();
}

