#include <iostream>
#include <vector>

using namespace std;

/*
 * 最大自序和
 * */

//暴力版本
int maxSubArray_(vector<int>& nums)
{
    if(nums.empty())
        return {};

    int max = nums[0];
    int len = nums.size();
    for(int i = 0; i < len; ++i)
    {
        int temp = nums[i];
        for(int j = i; j < len; ++j)
        {
            if(j > i)
                temp += nums[j];
            if(temp > max)
                max = temp;
        }
    }

    return max;
}

//dp版本
int _maxSubArray(vector<int>& nums)
{
    if(nums.empty())
        return {};
    int max = nums[0], pre = 0;
    for(auto& i : nums)
    {
        if(pre + i > i)
            pre = pre + i;
        else
            pre = i;
        if(pre > max)
            max = pre;
    }

    return max;
}


//线段树的版本，我也不知道为什么管这个东西叫简单，shit
struct Status
{
    int lSum;  //左区间和
    int rSum;  //右区间和
    int mSum;  //最大区间和
    int iSum;  //总区间和
};

Status pushUp(Status l, Status r)
{
    int iSum = l.iSum + r.iSum;
    int lSum = max(l.lSum, l.iSum + l.lSum);
    int rSum = max(r.rSum, r.iSum + l.rSum);
    int mSum = max(max(l.mSum, r.mSum), l.rSum + r.rSum);
    return (Status){lSum, rSum, mSum, iSum};
}

Status get(vector<int>& v, int l, int r)
{
    if(l == r) return (Status){v[l], v[l], v[l], v[l]};

    int m = (l + r) >> 1; //分段
    Status lSub = get(v, l, m);
    Status rSub = get(v, m + 1, r);
    return pushUp(lSub, rSub);
}

int maxSubArray(vector<int>& nums)
{
    return get(nums, 0, nums.size() - 1).mSum;
}

int main()
{
    vector<int> v{-2,-3,-1,-5};
    cout << maxSubArray(v) << endl;
}

