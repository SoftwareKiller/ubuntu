#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//会造成重复，不可取
vector<vector<int>> _threeSum(vector<int>& nums)
{
    if(nums.size() < 3)
        return {};

    vector<vector<int>> ret;
    int size = nums.size();
    for(int i = 0; i < size; ++i)
    {
        bool flag = false;
        for(int j = i + 1; j < size; ++j)
        {
            for(int k = j + 1; k < size; ++k)
            {
                vector<int> Node;
                int temp = nums[i] + nums[j] + nums[k];
                if(!temp)
                {
                    Node.push_back(nums[i]);
                    Node.push_back(nums[j]);
                    Node.push_back(nums[k]);
                    ret.emplace_back(move(Node));
                    flag = true;
                    break;
                }
            }
            if(flag)
                break;
        }
    }

    return ret;
}

vector<vector<int>> threeSum(vector<int>& nums)
{
    int len = nums.size();
    if(len < 3)
        return {};
    vector<vector<int>> ret;
    sort(nums.begin(), nums.end());

    for(int first = 0; first < len; ++first)
    {
        if(first > 0 && nums[first] == nums[first-1])
            continue;

        int target = -nums[first];
        int third = len - 1;

        for(int second = first + 1; second < len; ++second)
        {
            if(second > first + 1 && nums[second] == nums[second - 1])
                continue;

            while(second < third && nums[second] + nums[third] > target)
                --third;

            if(second == third)
                break;

            if(nums[second] + nums[third] == target)
                ret.push_back({nums[first], nums[second], nums[third]});
        }
    }

    return ret;
}

void printResult(vector<vector<int>> v)
{
    for(auto& it : v)
    {
        for(auto& sub : it)
        {
            cout << sub << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> v{-1, 0, 1, 2, -1, -4};
    printResult(threeSum(v));
}

