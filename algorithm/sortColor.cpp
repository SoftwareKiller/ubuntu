#include <iostream>
#include <vector>

using namespace std;

//双指针扫描类型的问题
void sortColor(vector<int>& color)
{
    int l = 0, r = color.size() - 1;
    int index = 0;
    while(index <= r)
    {
        if(color[index] == 0)
            swap(color[l++], color[index++]);
        else if(color[index] == 2)
            swap(color[index], color[r--]);
        else
            ++index;
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
    vector<int> v{1,2,2};
    sortColor(v);
    print(v);
    v = {2,0,1};
    sortColor(v);
    print(v);
}

