#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<vector<int>>);

void dfs(vector<vector<int>>& ret, vector<int>& v, vector<int>& path, int start, int target)
{
    if(target == 0)
    {
        ret.push_back({path});
        return;
    }

    for(int i = start; i  < v.size() && v[i] <= target; )
    {
        path.push_back(v[i]);
        dfs(ret, v, path, i + 1, target - v[i]);
        ++i;
        while(i > 0 && i < v.size() && v[i] == v[i-1])
            ++i;
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& v, int target)
{
    sort(v.begin(), v.end());
    vector<vector<int>> ret;
    vector<int> path;
    dfs(ret, v, path, 0, target);
    return ret;
}

void print(vector<vector<int>> v)
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
    vector<int> v{1,1};
    auto r = combinationSum2(v, 1);
    print(r);
}

