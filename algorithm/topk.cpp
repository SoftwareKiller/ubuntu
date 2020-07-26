#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& v, int l, int r)
{
    int x = v[r], i = l - 1;
    for(int j = l; j < r; ++j)
    {
        if(v[j] <= x)
            swap(v[++i], v[j]);
    }

    swap(v[i+1],v[r]);
    return i + 1;
}

int randomPartition(vector<int>&v, int l, int r)
{
    int i = rand() % (r - l + 1) + l;
    swap(v[i], v[r]);
    return partition(v, l, r);
}

void quick(vector<int>& v, int l, int r, int index)
{
    int q = randomPartition(v,l,r);
    if(q == index)
        return;
    else
        return q < index ? quick(v, q + 1, r, index) : \
            quick(v, l, q - 1, index);
}

vector<int> topk(vector<int>& v, int k)
{
    vector<int> ret;

    srand(time(0));
    quick(v, 0, v.size() - 1, v.size() - k);
    for(int i = k; i < v.size(); ++i)
        ret.push_back(v[i]);
    return ret;
}

void print(vector<int>& v)
{
    for(auto& i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v{11,9,112,23,34,7};

    auto ret = topk(v, 3);

    print(ret);
}

