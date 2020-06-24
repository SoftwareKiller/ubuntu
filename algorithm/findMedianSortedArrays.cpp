/*
 * 寻找两个有序数组的中位数，时间复杂度O(log(m + n))
 * 假设两个有序数组长度为m和n，算法时间复杂的为O(log(m + n))
 * 有序，log级别的复杂的，二分查找满足这一条件
 * 根据中位数定义，m + n为奇数，则中位数为第(m + n)/2，若为偶数，则为(m + n)/2和(m + n)/2 + 1个元素的平均值
 * 因此可转化为求两个有序数组中第k小的数，k为(m + n)/2或(m + n)/2 + 1
 * 通常在数组中k的值需要下标-1
 * */

#include <iostream>
#include <vector>

using namespace std;

int getKthElement(vector<int>& v1, vector<int>& v2, int k)
{
    int m = v1.size();
    int n = v2.size();

    int index1 = 0, index2 = 0;

    while(true)
    {
        if(m == index1)
        {
            return v2[index2 + k - 1];
        }
        if(n == index2)
        {
            return v1[index1 + k - 1];
        }
        if(k == 1)
        {
            return min(v1[index1], v2[index2]);
        }

        int newIndex1 = min(index1 + k/2 - 1, m - 1);
        int newIndex2 = min(index2 + k/2 - 1, n - 1);
        int val_1 = v1[newIndex1];
        int val_2 = v2[newIndex2];
        if(val_1 <= val_2)
        {
            k -= newIndex1 - index1 + 1;
            index1 = newIndex1 + 1;
        }
        else
        {
            k -= newIndex2 - index2 + 1;
            index2 = newIndex2 + 1;
        }
    }
}

double findMedianSortedArrays(vector<int>& numb1, vector<int>& numb2)
{
    //计算总长度，用于计算k值
    int total = numb1.size() + numb2.size();
    if(total % 2 == 1) //和为奇数的情况
    {
        return getKthElement(numb1, numb2, (total + 1) / 2); //第k小，所以total + 1，方便计算
    }
    else
    {
        return (getKthElement(numb1, numb2, total / 2) +
                getKthElement(numb1, numb2, (total / 2) + 1)) / 2.0;
    }
}

int main()
{
    vector<int> v1{1, 3};
    vector<int> v2{2};
    cout << findMedianSortedArrays(v1, v2) << endl;
}

