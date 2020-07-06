#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//我也没看懂，感觉挺简单的题，硬是做了好多次。。。
int firstMissingPositive(vector<int>& v)
{
    if(v.empty())
        return 1;
    sort(v.begin(), v.end());
    int count = 1;
    for(int i = 0; i < v.size();)
    {
        bool flag = false;
        if(v[i] > 0)
        {
            if(v[i]  == count)
            {
                while(i >= 0 && i < v.size() && v[i] == count)
                {
                    ++i;
                    flag = true;
                }
                ++count;
                if(!flag)
                {
                    ++i;
                    flag = false;
                }
                if(i == v.size())
                {
                    if(count == v[i-1])
                        return ++count;
                    return count;
                }
                continue;
            }
            else
                return count;
        }
        ++i;
    }
    return count;
}

int main()
{
    vector<int> v{1,2,2,2,2,3,1};
    cout << firstMissingPositive(v) << endl;
}

