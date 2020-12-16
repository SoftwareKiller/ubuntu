/*给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
  你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target)
{
    vector<int> location;
    if(nums.empty())
        return location;
    unordered_map<int, int> data;
    for(size_t i = 0; i < nums.size(); ++i)
    {
        data.insert(make_pair(nums[i], i));
    }

    for(size_t i = 0;i < nums.size(); ++i)
    {
        auto it = data.find(target - nums[i]);
        if(it != data.end() && it->second != i)
        {
            location.push_back(i);
            location.push_back(it->second);
            break;
        }
    }
    return  location;
}

int main()
{
    vector<int> vec{2, 7, 11, 15};
    int target = 9;
    vector<int> ret;
    ret = twoSum(vec, target);
    cout << vec[0] << " " << vec[1] << " " << vec[0] + vec[1] << endl;
    return 0;
}

