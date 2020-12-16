#include <iostream>
#include <vector>

using namespace std;

int binarySearch(const vector<int>& vec, const int key)
{
    if(vec.empty())
        return -1;
    int size = vec.size();
    int low = 0;
    int high = size - 1;
    while(low <= high)
    {
        int mid = low + (high - low)/2;
        //注意边界增加是否正确
        if(vec[mid] == key)
            return mid;
        else if(vec[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

int main()
{
    vector<int> vec{1, 2, 4, 7, 9, 11};
    int key = 7;
    int ret = binarySearch(vec, key);
    cout << ret << endl;
    if(ret >= 0)
        cout << vec[ret] << endl;
    return 0;
}

