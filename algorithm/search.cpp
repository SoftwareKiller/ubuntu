#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& v, int target)
{
    if(v.empty())
        return -1;
    if(v.size() == 1)
        return v[0] == target ? 0 : -1;
    int l = 0;
    int r = v.size() - 1;
    int pos = 0;
    while(l <= r)
    {
        pos = (r-l)/2 + l;
        if(v[pos] == target)
            return pos;
        if(v[0] <= v[pos])
        {
            if(v[0] <= target && target < v[pos])
                r = pos - 1;
            else
                l = pos + 1;
        }
        else
        {
            if(v[pos] < target && target <= v[v.size() - 1])
                l = pos + 1;
            else
                r = pos - 1;
        }
    }

    return -1;
}

int main()
{
    vector<int> v{5,1,2};
    cout << search(v, 2) << endl;
}

