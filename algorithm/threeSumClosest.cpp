#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//有部分案例不能通过，[-3, -2, -5, 3, -4]，因为不能探测到所有情况
int threeSumClosest_(vector<int>& nums, int target)
{
    int n = nums.size();
    if(n < 3)
        return target;

    int ret = nums[0] + nums[1] + nums[2];
    int diff = abs(target - ret);
    for(int i = 0; i < n; ++i)
    {
        int k = n - 1;
        for(int j = i + 1; j < n; ++j)
        {
            if(j >= k)
                break;
            int temp = nums[i] + nums[j] + nums[k];
            if(temp == target)
                return temp;
            else if(abs(temp - target) < diff)
            {
                ret = temp;
                diff = abs(temp - target);
            }
            --k;
        }
    }

    return ret;
}

int threeSumClosest(vector<int>& nums, int target)
{
    int n = nums.size();
    if(n < 3)
        return target;

    sort(nums.begin(), nums.end());

    int ret = nums[0] + nums[1] + nums[2];
    int diff = abs(target - ret);
    for(int i = 0; i < n; ++i)
    {
        if(i > 0 && nums[i] == nums[i-1])
            continue;
        int j = i + 1;
        int k = n - 1;
        while(j < n)
        {
            if(j >= k)
                break;
            int temp = nums[i] + nums[j] + nums[k];
            int d = abs(temp - target);
            if(temp == target)
                return temp;
            else if(d < diff)
            {
                ret = temp;
                diff = d;
            }
            if(temp < target)
                ++j;
            else
                --k;
        }
    }

    return ret;
}

int main()
{
    vector<int> v{-1,2,1,-4};
    cout << threeSumClosest(v, 1) << endl;
    vector<int> v1{-3,-2,-5,3,-4};
    cout << threeSumClosest(v1, -1) << endl;
    vector<int> v2{0,2,1,-3};
    cout << threeSumClosest(v2, 1) << endl;
}

