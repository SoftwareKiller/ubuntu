#include <cstdlib>
#include <iostream>
#include <utility>
#include <list>
#include <unordered_map>


typedef std::pair<int, int> Node;
//hash存值需要遍历链表才能删除，可以直接存指针或迭代器
class lru
{
public:
    lru(size_t cap = 100)
        :length(0),
        data_(cap),
        dict_(cap)
    {}
    const int get(int key)
    {
        if(!exist(key))
            return -1;
        else
        {
            Node tmp;
            auto it = dict_.find(key);
            tmp.first = it->second.first;
            tmp.second = it->second.second;
            moveData(tmp);
        }
        return dict_.find(key)->second.second;
    }

    void put(Node data)
    {
        if(exist(data.first))
        {
            moveData(data);
        }
        else
        {
            if(length == capacity_)
            {
                Node tmp = data_.back();
                data_.pop_back();
                dict_.erase(dict_.find(tmp.first));
                dict_.insert({data.first, data});
            }
            else
            {
                data_.push_front(data);
                dict_.insert(std::make_pair(data.first, data));
                ++length;
            }
        }
    }

    const size_t size()
    {
        return length;
    }

private:
    bool exist(int key)
    {
        return dict_.find(key) != dict_.end();
    }
    bool moveData(Node tmp)
    {
        bool flag = false;
        for(std::list<Node>::iterator it = data_.begin(); it != data_.end(); ++it)
        {
            if(it->first == tmp.first)
            {
                Node tmp;
                tmp.first = it->first;
                tmp.second = it->second;
                data_.erase(it);
                data_.push_front(tmp);
                flag = true;
                break;
            }
        }
        return flag;
    }

private:
    const static size_t capacity_ = 100;
    size_t length;
    std::list<Node> data_;
    std::unordered_map<int, Node> dict_;
};

class fast_lru
{
public:
    fast_lru(size_t cap = 100) : capacity_(cap)
    {}
    ~fast_lru() = default;

    int get(int k)
    {
        auto it = hash_.find(k);
        if(it == hash_.end())
            return -1;

        Node newpos{k, it->second->second};
        data_.erase(it->second);
        data_.emplace_front(std::move(newpos));
        hash_[k] = data_.begin();
        return data_.front().second;
    }

    void put(Node newNode)
    {
        int k = newNode.first;
        auto it = hash_.find(k);
        if(it != hash_.end())
        {
            data_.erase(it->second);
            data_.push_front(std::move(newNode));
            hash_[k] = data_.begin();
        }
        else
        {
            if(data_.size() == capacity_)
            {
                hash_.erase(data_.back().first);
                data_.pop_back();
            }
            data_.push_front(std::move(newNode));
            hash_.insert(make_pair(k, data_.begin()));
        }
    }

    size_t size()
    {
        return data_.size();
    }
private:
    const size_t capacity_ = 100;
    std::list<Node> data_;
    std::unordered_map<int, std::list<Node>::iterator> hash_;
};

int main()
{
    using namespace std;
    Node data1{9, 10}; 
    Node data2{1, 8}; 
    Node data3{4, 5}; 
    Node data4{2, 11}; 
    Node data5{9, 11}; 
    fast_lru cache;
    cache.put(data1);
    cout << "lru size: " << cache.size() << " key = 8, value = " << cache.get(data1.first) << endl;
    cache.put(data2);
    cache.put(data3);
    cache.put(data4);
    cache.put(data5);
    cout << "lru size: " << cache.size() << " value = " << cache.get(data5.first) << endl;
    cout << "lru size: " << cache.size() << " value = " << cache.get(data4.first) << endl;
    cout << "lru size: " << cache.size() << " value = " << cache.get(data3.first) << endl;

}

