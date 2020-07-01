#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& v, int val)
{
    int n = v.size();
    int k = 0;
    for(int i = 0; i < n; ++i)
    {
        if(v[i] != val)
        {
            v[k] = v[i];
            ++k;
        }
    }

    return k;
}

int main()
{
    vector<int> v{0,1,2,2,3,0,4,2};
    cout << removeElement(v, 2) << endl;
}

