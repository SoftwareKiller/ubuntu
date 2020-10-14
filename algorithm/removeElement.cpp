#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int removeElement(vector<int>& v, int val)
{
    size_t n = v.size();
    size_t index = 0;
    for(int i = 0; i < n; ++i)
    {
        if(v[i] != val)
            v[index++] = v[i];
    }

    return index;
}

int stl_removeElement(vector<int>& v, int val)
{
    return distance(v.begin(), remove(v.begin(), v.end(), val));
}

int main()
{
    vector<int> v{0,1,2,2,3,0,4,2};
    cout << removeElement(v, 2) << endl;
    cout << stl_removeElement(v, 4) << endl;
}

