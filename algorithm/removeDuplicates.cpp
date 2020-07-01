#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& v)
{
    int i = 0;
    int n = v.size();
    for(int j = 1; j < n; ++j)
    {
        if(v[i] != v[j])
        {
            ++i;
            v[i] = v[j];
        }
    }

    return i + 1;
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
    cout << removeDuplicates(v) << endl;
    print(v);
}

