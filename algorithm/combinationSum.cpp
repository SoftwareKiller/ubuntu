#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>>& ret, vector<int>& v, vector<int>& path, int start, int target)
{
    if(target == 0)
    {
        ret.push_back({path});
        return;
    }

    for(int i = start; i < v.size() && v[i] <= target; ++i)
    {
        path.push_back(v[i]);
        dfs(ret, v, path, i, target - v[i]);
        path.pop_back();
    }
}

//刚开始的思路的对v进行回溯，结果越写越复杂，应该是对target进行回溯
//排序是为了剪枝，减少搜索区间
vector<vector<int>> combinationSum(vector<int>& v, int target)
{
    sort(v.begin(), v.end());
    vector<vector<int>> ret;
    vector<int> path;
    dfs(ret, v, path, 0, target);
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
    vector<int> v{8,7,4,3};
    auto ret = combinationSum(v, 11);
    print(ret);
}

