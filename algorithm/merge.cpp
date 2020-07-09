#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<vector<int>>&);

vector<vector<int>> merge_(vector<vector<int>>& v)
{
    if(v.empty()) return {};
    sort(v.begin(), v.end());
    int n = v.size();
    vector<vector<int>> ret;
    bool flag = false;
    for(int i = 0; i < n; ++i)
    {
        vector<int> ans;
        if(i < n - 1 && v[i][0] <= v[i+1][0] && v[i][1] >= v[i+1][0])
        {
            int temp = v[i+1][1] >= v[i][1] ? v[i+1][1] : v[i][1];
            ans = {v[i][0], temp};
            if(flag)
            {
                ans[0] = ret.back()[0];
                ret.pop_back();
            }
            flag = true;
        }
        else
        {
            if(i < n && flag )
            {
                ++i;
                flag = false;
                if(i == n) break;
            }
            ans = {v[i][0], v[i][1]};
        }
        if(!ret.empty() && ret.back()[0] <= ans[0] && ret.back()[1] >= ans[1])
            continue;
        ret.emplace_back(ans);
    }

    return ret;
}

vector<vector<int>> merge(vector<vector<int>> v)
{
    if(v.empty())
        return {};

    sort(v.begin(),v.end());
    vector<vector<int>> ret;
    for(int i = 0; i < v.size(); ++i)
    {
        int l = v[i][0], r = v[i][1];
        if(ret.empty() || ret.back()[1] < l)
            ret.push_back({l,r});
        else
            ret.back()[1] = max(ret.back()[1], r);
    }

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
    vector<vector<int>> v{{2,3},{4,6},{1,10}};
    v = {{2,3},{2,2},{3,3},{4,6},{5,7}};
    auto ret = merge(v);
    print(ret);

    vector<vector<int>> vv{{1,4},{0,2},{3,5}};
    ret = merge(vv);
    print(ret);
}

