#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/*
 * n = 0, [0]
 * n = 1, [0,1] //新的元素1，为0+2^0
 * n = 2, [0,1,3,2] // 新的元素[3,2]为[0,1]->[1,0]后分别加上2^1
 * n = 3, [0,1,3,2,6,7,5,4] // 新的元素[6,7,5,4]为[0,1,3,2]->[2,3,1,0]后分别加上2^2->[6,7,5,4]
 */

vector<int> grayCode(int n)
{
    vector<int> res{0};
    for(int i = 0; i < n; ++i)
    {
        int len = res.size();
        for(int j = 0; j < len; ++j)
        {
            res.push_back(res[len - j - 1] + pow(2, i));
        }
    }

    return res;
}

void print(vector<int>& v)
{
    for(auto& i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    auto ret = grayCode(4);
    print(ret);
}

