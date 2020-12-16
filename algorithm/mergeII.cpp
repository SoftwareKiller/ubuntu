#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& v, int m, vector<int>& v2, int n)
{
    int len = m + n - 1;
    --n;
    --m;
    while(n >= 0)
    {
        if(m >= 0 && v[m] >= v2[n])
            v[len--] = v[m--];
        else
            v[len--] = v2[n--];
    }
}

void print(vector<int>& v)
{
    for(auto& i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v{1,2,9,0,0,0};
    vector<int> v2{3,5,9};
    merge(v, 3, v2, 3);
    print(v);
}

