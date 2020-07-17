#include <iostream>
#include <vector>

using namespace std;

void backtrace(vector<vector<int>>& ret, vector<int>& v, vector<int>& trace, int start)
{
    /*bool flag = true;
    for(int i = 0; i < ret.size(); ++i)
    {
        if(ret[i].size() != trace.size())
            continue;
        else if(ret[i] == trace)
        {
            flag = false;
            break;
        }
    }
    if(flag)*/
    ret.push_back(trace);

    for(int i = start; i < v.size(); ++i)
    {
        if(i > start && v[i] == v[i-1])
            continue;
        trace.push_back(v[i]);
        backtrace(ret, v, trace, i + 1);
        trace.pop_back();
    }
}

vector<vector<int>> subsetWithDup(vector<int>& v)
{
    if(v.empty()) return {};

    vector<vector<int>> ret;
    vector<int> trace;
    backtrace(ret, v, trace, 0);
    return ret;
}

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(auto& j: i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<int> v{1,2,2};
    auto ret = subsetWithDup(v);
    print(ret);
}

