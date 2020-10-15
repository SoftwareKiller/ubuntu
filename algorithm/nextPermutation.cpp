#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void nextPermutation(vector<int>& v)
{
    if(v.size() < 2)
        return;
    bool flag = true;
    int n = v.size();
    for(int i = n-1; i > 0; --i)
    {
        if(v[i] > v[i-1])
        {
            flag = false;
            reverse(v.begin() + i, v.end());
            int pos = i;
            for(; i < n; ++i)
            {
                if(v[pos-1] < v[i])
                {
                    swap(v[i], v[pos-1]);
                    break;
                }
            }
            break;
        }
    }

    if(flag)
        reverse(v.begin(), v.end());
}

void print(vector<int> v)
{
    for(auto i : v)
        cout << i << " ";
    cout << endl;
}

void nextPermutation(vector<int>::iterator begin, vector<int>::iterator end)
{
    next_permutation(begin, end);
}

int main()
{
    vector<int> v{1,2,3};
    print(v);
    nextPermutation(v.begin(), v.end());
    //nextPermutation(v);
    print(v);
    vector<int> vv{3,2,1};
    print(vv);
    nextPermutation(vv.begin(), vv.end());
    //nextPermutation(vv);
    print(vv);
    vector<int> vvv{9,8,9,7};
    print(vvv);
    //nextPermutation(vvv);
    nextPermutation(vvv.begin(), vvv.end());
    print(vvv);
}

