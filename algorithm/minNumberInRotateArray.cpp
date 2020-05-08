/*
 * 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。*/
#include <vector>
#include <iostream>

using namespace std;

int minNumberInRoteteArray(const vector<int>& array)
{
    if(array.empty())
        return 0;
    if(array.size() == 1)
        return array[0];

    int left = 0;
    int right = array.size() - 1;
    int mid = left;
    while(array[left] >= array[right])
    {
        if(right - left == 1)
        {
            mid = right;
            break;
        }

        mid = right - (right - left) / 2;

        if(array[mid] >= array[right]) //此时仍然在较大的一段
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    return array[mid];
}

int main()
{
    vector<int> arr{3,4,5,1,2};
    cout << minNumberInRoteteArray(arr) << endl;
    vector<int> arr1{1,2,3,4,5};
    cout << minNumberInRoteteArray(arr1) << endl;
    vector<int> arr2{3,4,5,1};
    cout << minNumberInRoteteArray(arr2) << endl;
    return 0;
}

