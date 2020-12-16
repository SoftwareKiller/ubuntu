#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> fourSum(vector<int>& v, int target)
{
    int n = v.size();
    if(n < 4)
        return {};

    sort(v.begin(), v.end());
    vector<vector<int>> ret;
    for(int i = 0; i < n; ++i)
    {
        if(i > 0 && v[i] == v[i-1])
            continue;

        for(int j = i + 1; j < n; ++j)
        {
            if(j > i + 1 && v[j] == v[j-1])
                continue;
            int k = j + 1;
            int d = n - 1;
            while(k < d)
            {
                int temp = v[i] + v[j] + v[k] + v[d];
                if(temp < target)
                    ++k;
                else if(temp > target)
                    --d;
                if(temp == target)
                {
                    ret.push_back({v[i], v[j], v[k], v[d]});
                    while(k < d && v[k+1] == v[k])
                        ++k;
                    while(k < d && v[d-1] == v[d])
                        --d;
                    ++k;
                    --d;
                }
            }
        }
    }

    return ret;
}

void Print(vector<vector<int>> v)
{
    for(auto& i : v)
    {
        for(auto& j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> v{-3,-2,-1,0,0,1,2,3};
    Print(fourSum(v, 0));
}

