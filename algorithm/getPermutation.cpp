#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(auto& j : i)
            cout << j << " ";
        cout << endl;
    }
}

void backtrace(vector<vector<int>>& ret, vector<int>& v, int start)
{
    if(start == v.size())
    {
        ret.push_back(v);
        return;
    }

    for(int i = start; i < v.size(); ++i)
    {
        swap(v[i], v[start]);
        backtrace(ret, v, start + 1);
        swap(v[i], v[start]);
    }
}

//回溯
string getPermutation_(int n, int k)
{
    vector<int> permu;
    for(int i = 1; i <= n; ++i)
        permu.push_back(i);

    vector<vector<int>> ret;
    vector<int> path;
    backtrace(ret, permu, 0);
    //sort(ret.begin(), ret.end());
    if(k > ret.size())
        return "";
    print(ret);
    string s;
    for(int i = 0; i < n; ++i)
        s += (ret[k-1][i] + '0');

    return s;
}

template<typename It>
bool next_permutation(It first, It last)
{
    if(first == last) return false;
    It i = last;
    if(first == --i) return false;

    while(true)
    {
        It i1, i2;
        i1 = i;

        if(*--i < *i1)
        {
            i2 = last;
            while(!(*i < *--i2)) ;
            iter_swap(i,i2);
            reverse(i1, last);
            return true;
        }

        if(i == first)
        {
            reverse(first, last);
            return false;
        }
    }
}

string getPermutation(int n, int k)
{
    string s = string("123456789").substr(0, n);
    for(int j = 1; j < k; ++j)
        ::next_permutation(s.begin(), s.end());

    return s;
}

int main()
{
    cout << getPermutation(9,24) << endl;
}

