#include <iostream>
#include <vector>

using namespace std;

bool search_target(vector<int>& v, int target)
{
    int l = 0, r = v.size() - 1;
    int mid = 0;
    while(l <= r)
    {
        mid = (r - l)/2 + l;
        if(v[mid] == target)
            return true;
        else if(v[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return false;
}

bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    //这玩意还能分两种情况，我人傻了
    if(matrix.empty() || matrix[0].empty()) return false;

    //第0行为low，最后一行为high
    int low = 0, high = matrix.size() - 1, left = 0, right = matrix[0].size() - 1;
    int mid_lh = 0;
    while(low <= high)
    {
        mid_lh = (high - low) / 2 + low;
        if(matrix[mid_lh][left] <= target && matrix[mid_lh][right] >= target)
            return search_target(matrix[mid_lh], target);
        else if(matrix[mid_lh][left] < target)
            low = mid_lh + 1;
        else
            high = mid_lh - 1;
    }

    return false;
}

int main()
{
    vector<vector<int>> v{{1,3,5,7}, {10,11,16,20}, {23, 30, 34, 50}};
    cout << searchMatrix(v, 5) << endl;
}

