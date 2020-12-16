#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <asio.hpp>

using namespace std;

mutex global_stream_mutex;

#if !defined (ASIO_NO_DEPRECATED)
typedef asio::io_service io_context;
#endif

void work_thread(shared_ptr<io_context> sp_ioc)
{
    {
        unique_lock<mutex> lock{global_stream_mutex};
        cout << "[" << this_thread::get_id() << "] work is stared. " << endl;
    }

    sp_ioc->run();

    {
        unique_lock<mutex> lock{global_stream_mutex};
        cout << "[" << this_thread::get_id() << "] work is finished." << endl;
    }
}

size_t fib(size_t n)
{
    if(n <= 2)
        return n;

    return fib(n - 1) + fib(n - 2);
}

void Calculate_fib(size_t n)
{

    {
        unique_lock<mutex> lock{global_stream_mutex};
        cout << "[" << this_thread::get_id() << "] fib( " << n << " ) start" << endl;
    }

    auto f = fib(n);

    {
        unique_lock<mutex> lock{global_stream_mutex};
        cout << "[" << this_thread::get_id() << "] fib( " << n << " ) = " << f << endl;
    }
}

int main()
{
    shared_ptr<io_context> sp_ioc = make_shared<io_context>();
    shared_ptr<io_context::work> sp_iwork= make_shared<io_context::work>(*sp_ioc);

    {
        unique_lock<mutex> lock{global_stream_mutex};
        cout << "[" << this_thread::get_id() << "] This Program will exit when all work has finished" << endl;
    }

    thread t1(bind(&work_thread, sp_ioc));
    thread t2(bind(&work_thread, sp_ioc));

    sp_ioc->post(bind(&Calculate_fib, 3));
    sp_ioc->post(bind(&Calculate_fib, 4));
    sp_ioc->post(bind(&Calculate_fib, 5));

    sp_iwork.reset();

    t1.join();
    t2.join();
}
