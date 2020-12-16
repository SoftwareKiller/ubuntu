#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void backtrace(vector<vector<int>>& ret, vector<int>& v, vector<int>& path, vector<bool>& flag)
{
    if(v.size() == path.size())
    {
        ret.emplace_back(path);
        return;
    }

    for(int i = 0; i < v.size(); ++i)
    {
        if(!flag[i])
            continue;
        if(i > 0 && v[i] == v[i-1] && flag[i-1])
            continue;
        path.push_back(v[i]);
        flag[i] = false;
        backtrace(ret, v, path, flag);
        flag[i] = true;
        path.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& v)
{
    sort(v.begin(), v.end());
    vector<vector<int>> ret;
    vector<int> path;
    vector<bool> flag(v.size(), true);
    backtrace(ret, v, path, flag);
    return ret;
}

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(auto& j : i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<int> v{3, 3, 0, 3};
    auto ret = permuteUnique(v);
    print(ret);
}

