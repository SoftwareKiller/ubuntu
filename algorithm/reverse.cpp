#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

int reverse(int x)
{
    bool flag = x >= 0 ? true : false;

    x = abs(x);
    int ret = 0;
    int bit = 0;
    while(x)
    {
        int temp = x % 10;
        if(bit != 0)
            ret *= 10;
        ret += temp;
        x /= 10;
        ++bit;
    }

    if(!flag)
        ret = 0 - ret;
    if(ret > INT_MAX || ret < INT_MIN)
        return 0;

    return ret;
}

int main()
{
    cout << reverse(123) << " " << reverse(-123) << " " << reverse(120) << endl;
}

