#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsets_(vector<int>& v)
{
    if(v.empty()) return {{}};

    int n = v.back();
    v.pop_back();

    vector<vector<int>> ret = subsets_(v);

    int size = ret.size();
    for(int i = 0; i < size; ++i)
    {
        ret.push_back(ret[i]);
        ret.back().push_back(n);
    }

    return ret;
}

void backtrack(vector<vector<int>>& ret, vector<int>& v,  vector<int>& track, int start)
{
    ret.push_back(track);

    for(int i = start; i < v.size(); ++i)
    {
        track.push_back(v[i]);
        backtrack(ret, v, track, i + 1);
        track.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& v)
{
    vector<vector<int>> ret;
    vector<int> track;
    backtrack(ret, v, track, 0);
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
    vector<int> v{1,2,3};
    auto ret = subsets(v);
    print(ret);
}

