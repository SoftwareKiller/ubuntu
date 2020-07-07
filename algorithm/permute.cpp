#include <iostream>
#include <vector>

using namespace std;

void permute_(vector<vector<int>>& ret, vector<int>&v, vector<int>& path)
{
    if(path.size() == v.size())
    {
        ret.emplace_back(path);
        return;
    }

    for(int i = 0; i < v.size(); ++i)
    {
        bool flag = false;
        for(int j = 0; j < path.size(); ++j)
        {
            if(v[i] == path[j])
            {
                flag = true;
                break;
            }
        }
        if(flag)
            continue;
        path.push_back(v[i]);
        permute_(ret, v, path);
        path.pop_back();
    }
}

vector<vector<int>> permute(vector<int>& v)
{
    vector<vector<int>> ret;
    vector<int> path;
    permute_(ret, v, path);
    return ret;
}

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(int& j : i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<int> v{1,2,3};
    auto ret = permute(v);
    print(ret);
}

