#include <iostream>
#include <vector>

using namespace std;

vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> ret;
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    bool flag = false;
    int mid = 0;
    while(l <= r)
    {
        mid = (r - l)/2 + l;
        if(target == nums[mid])
        {
            flag = true;
            break;
        }

        if(nums[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }

    if(flag)
    {
        l = mid , r = mid;
        while(true)
        {
            if(l > 0 && nums[l-1] == target)
                --l;
            else if(r < n-1 && nums[r+1] == target)
                ++r;
            else
                break;
        }
        ret.push_back(l);
        ret.push_back(r);
    }
    else
    {
        ret.push_back(-1);
        ret.push_back(-1);
    }

    return ret;
}

void print(vector<int> v)
{
    for(auto& i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v{1,1};
    auto r = searchRange(v, 1);
    print(r);
}

