#include <iostream>
#include <vector>

using namespace std;

void backtrace(vector<vector<int>>& ret, vector<int>& path, int start, int n, int k)
{
    if(path.size() == k)
    {
        ret.emplace_back(path);
        return;
    }

    for(int i = start; i <= n - (k - path.size()) + 1; ++i)
    {
        path.push_back(i);
        backtrace(ret, path, i + 1, n, k);
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int k)
{
    if(n <= 0 || k <= 0 || k > n)
        return {};
    vector<vector<int>> ret;
    vector<int> path;
    backtrace(ret, path, 1, n, k);
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
    auto ret = combine(5, 3);
    print(ret);
}

