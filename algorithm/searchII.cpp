#include <iostream>
#include <vector>

using namespace std;

bool search(vector<int>& v, int target)
{
    int l = 0, r = v.size() - 1;
    while(l <= r)
    {
        int mid = ((r-l)>>1) + l;
        if(v[mid] == target) return true;

        if(v[mid] > v[l])
        {
            if(v[mid] > target && target >= v[l])
                r = mid - 1;
            else
                l = mid + 1;
        }
        else if(v[mid] < v[r])
        {
            if(v[mid] < target && target <= v[r])
                l = mid + 1;
            else
                r = mid - 1;
        }
        else
        {
            if(v[mid] == v[l]) ++l;
            if(v[mid] == v[r]) --r;
        }
    }

    return false;
}

int main()
{
    vector<int> v{2,5,6,0,0,1,2};
    cout << search(v, 6) << endl;
}

