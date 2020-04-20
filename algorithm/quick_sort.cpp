#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void quick_sort(vector<int>& vec, int left, int right)
{
    if(left > right)
        return;

    int base = vec[left];
    int i = left, j = right;
    while(i < j)
    {
        while(i < j && vec[j] >= base)
            --j;

        vec[i] = vec[j];

        while(i < j && vec[i] <= base)
            ++i;

        vec[j] = vec[i];
    }
    vec[i] = base;

    quick_sort(vec, left, i - 1);
    quick_sort(vec, i + 1, right);
}

void display(vector<int>& vec)
{
    for(auto it : vec)
        cout << it << " ";
    cout << endl;
}

int main()
{
    srand(time(nullptr));
    vector<int> vec;
    for(size_t i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 150);
    }
    display(vec);

    quick_sort(vec, 0, vec.size() - 1);

    display(vec);

    return 0;
}

