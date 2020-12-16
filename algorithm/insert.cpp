#include <iostream>
#include <vector>

using namespace std;

void print(vector<vector<int>>& v)
{
    for(auto& it : v)
    {
        for(auto& j : it)
            cout << j << " ";
        cout << ",";
    }
    cout << endl;
}

vector<vector<int>> insert(vector<vector<int>>& v, vector<int>& val)
{
    if(v.empty())
        return {val};
    if(val.empty())
        return v;
    vector<vector<int>> ret{};
    int l = val[0], r = val[1];
    int i = 0;
    for(; i <v.size(); ++i)
    {
        if(v[i][1] < l)
            ret.push_back(v[i]);
        else
        {
            if(v[i][0] < l)
            {
                ret.push_back(v[i]);
                v[i] = {l,r};
            }
            else
                ret.push_back({l,r});
            break;
        }
    }

    if(i == v.size())
    {
        ret.push_back({l,r});
    }
    for(; i < v.size(); ++i)
    {
        l = v[i][0], r = v[i][1];
        if(ret.back()[1] < l)
            ret.push_back({l, r});
        else
            ret.back()[1] = max(ret.back()[1], r);
    }

    return ret;
}

int main()
{
    vector<vector<int>> v{{1,5}};

    vector<int> val{6,8};
    auto ret = insert(v, val);
    print(ret);
    v = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    val = {4,8};
    ret = insert(v, val);
    print(ret);
}

