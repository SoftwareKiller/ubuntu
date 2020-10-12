#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& v, int target)
{
    int l = 0, r = v.size() - 1;
    while(l <= r)
    {
        int mid = ((r-l)>>1) + l;
        if(v[mid] == target) return mid;

        if(v[l] < v[mid])
        {
            if(v[l] <= target && target < v[mid])
                r = mid;
            else
                l = mid;
        }
        else if(v[l] > v[mid])
        {
            if(v[mid] < target && target <= v[r])
                l = mid;
            else
                r = mid;
        }
        else
        {
            if(v[mid] == v[l]) ++l;
            if(v[mid] == v[r]) --r;
        }
    }

    return -1;
}

int main()
{
    vector<int> v{2,5,6,0,0,1,2};
    cout << search(v, 6) << endl;
    cout << search(v, 0) << endl;
    cout << search(v, 2) << endl;
}

