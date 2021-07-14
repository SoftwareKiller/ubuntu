#include <iostream>
#include <vector>

using namespace std;

vector<int> reOrderArray(vector<int>& array)
{
    if(array.size() <= 1)
    {
        return array;
    }
    
    vector<int> result;
    result.resize(array.size());

    size_t head = 0, tail = array.size() - 1;
    size_t idx_head = head, idx_tail = tail;
    while(idx_head <= idx_tail)
    {
        if(array.at(head) & 0x1)
        {
            result[idx_head] = array.at(head);
            ++idx_head;
        }
        if((array.at(tail) & 0x1) == 0)
        {
            result[idx_tail] = array.at(tail);
            --idx_tail;
        }
        ++head, --tail;
    }

    return result;
}

vector<int> bubbleSort(vector<int>& array)
{
    if(array.size() <= 1)
    {
        return array;
    }

    bool flag = true;
    while(flag)
    {
        flag = false;
        for(size_t j = 0; j < array.size(); ++j)
        {
            if(j > 0 && (array.at(j - 1) & 0x1) == 0 && (array.at(j) & 0x1))
            {
                swap(array[j-1], array[j]);
                flag = true;
            }
        }
    }

    return array;
}

void print(vector<int>& v)
{
    for(auto& it : v)
    {
        cout << it << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> v = {2,4,6,5,7};
    //auto res = reOrderArray(v);
    auto res = bubbleSort(v);
    print(res);
    return 0;
}

