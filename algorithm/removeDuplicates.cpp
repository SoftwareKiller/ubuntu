#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& v, int k)
{
    int i = 0;
    int n = v.size();
    for(int j = 1; j < n; ++j)
    {
        if(v[i] != v[j])
            v[++i] = v[j];
    }

    return i + 1;
}

int removeDuplicates(vector<int> v)
{
    return distance(v.begin(), unique(v.begin(), v.end()));
}

void print(vector<int>& v)
{
    for(auto& i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> v{0, 0, 1, 1, 2, 2, 3, 3, 4};
    cout << removeDuplicates(v, 0) << endl;
    print(v);
}

