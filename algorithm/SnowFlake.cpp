/*
 * 使用SnowFlake算法构建分布式ID生成器
 * */

#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

class IdWorker
{
public:
    IdWorker(int32_t masterId, int32_t NodeId)
    {
        id_.id = 0;
        id_.st.masterId = masterId;
        id_.st.NodeId = NodeId;
    }

    int64_t CreateId()
    {
        auto timestamp = GetMillionSecond();
        std::unique_lock<mutex> lock{ mutex_ };

        if(timestamp < last_timestamp_)
        {//出现当前时间小于上一次ID生成时间，说明系统时钟发生回退
            auto offset = last_timestamp_ - timestamp;
            if(offset <= 10)
            {
                std::this_thread::sleep_for(chrono::milliseconds(offset * 2));

                timestamp = GetMillionSecond();
            }
            else
            {
                id_.st.timeRollBack++;
            }
        }

        if(last_timestamp_ == timestamp)
        {
            //同时生成，进行排序
            id_.st.sequence++;
            if(0 == id_.st.sequence)
            {
                //发生溢出,等一毫秒
                timestamp = WaitMillionSecond(last_timestamp_);
            }
        }
        else
            id_.st.sequence = 0;

        last_timestamp_ = timestamp;
        id_.st.timestamp = timestamp - START_TIME;
        return id_.id;
    }

private:
    int64_t GetMillionSecond() const
    {
        auto timestamp = chrono::time_point_cast<chrono::milliseconds>(chrono::steady_clock::now());
        return timestamp.time_since_epoch().count();
    }

    int64_t WaitMillionSecond(int64_t last_timestamp) const
    {
        auto now = GetMillionSecond();
        while(now <= last_timestamp)
        {
            now = GetMillionSecond();
        }
        return now;
    }

private:
    struct StId{
        int64_t sequence : 10;
        int64_t NodeId : 5;
        int64_t masterId : 5;
        int64_t timeRollBack : 5;
        int64_t timestamp: 38;
        int64_t unused : 1;
    };

    union UnionId
    {
        StId st;
        int64_t id;
    };

    const int64_t START_TIME = 1577808000; //2020-1-1:0:0:0

    std::mutex mutex_;

    int64_t last_timestamp_ = 0;
    UnionId id_;
};

bool flag = true;

void Count()
{
    FILE* fp = fopen("id", "w+");
    char buf[64] = { 0 };
    IdWorker id_worker(5, 6);
    int64_t count = 0;
    int64_t id = 0;
    while(flag)
    {
        id = id_worker.CreateId();
        sprintf(buf, "%ld\r\n", id);
        fwrite(buf, 1, 20, fp);
        ++count;
    }
    fclose(fp);

    cout << count << endl;
}

int main()
{
    thread t1(Count);

    this_thread::sleep_for(chrono::seconds(1));

    flag = false;
    t1.join();
}

