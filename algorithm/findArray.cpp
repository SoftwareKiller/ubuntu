#include <vector>
#include <iostream>

/*
 * 在一个矩阵中查找是否存在某个值
 * 矩阵从左到右递增
 * 从上到下递增
 * */

using namespace std;

/*
 * 因为矩阵的递增特性，故而不可以从左上或右下查找
 * 只能从左下或右上查找，这里选择左下*/

bool findArray(int target, vector<vector<int>>& arr)
{
    if(arr.empty())
        return false;
    int high = arr.size();
    int right = arr[0].size();
    int i,j;
    for(i = high - 1, j = 0; i >= 0&& j < right;)
    {
        if(target == arr[i][j])
            return true;
        else if(target > arr[i][j])
        {
            ++j;
        }else
        {
            --i;
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> array{ {1,2,8,9},
                               {2,4,9,12},
                               {4,7,10,13},
                               {6,8,11,15} };
    cout << findArray(7, array) << endl;
    cout << findArray(14, array) << endl;
    cout << findArray(21, array) << endl;
    cout << findArray(0, array) << endl;
    return 0;
}

