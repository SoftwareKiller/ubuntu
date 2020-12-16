#include <iostream>

using namespace std;

int mySqrt_(int x)
{
    if(x <= 1)
        return x;

    int ret = 1;
    for(long long i = 2; i <= x/2; ++i)
    {
        ret = i * i;
        if(ret == x)
            return i;
        else if(ret > x)
            return i - 1;
        ret = i;
    }

    return ret;
}

int mySqrt(int x)
{
    if(x < 2)
        return x;

    int l = 1, r = x/2;

    long long mid = (r-l)/2 + l;
    while(l <= r)
    {
        mid = (r-l)/2 + l;
        long long pre = (mid - 1) * (mid - 1);
        long long ret = mid * mid;
        if(ret == x) return mid;
        if(ret > x && pre < x) return mid - 1;
        else if(ret > x) r = mid - 1;
        else l = mid + 1;
    }

    return mid;
}

int main()
{
    cout << mySqrt(1) << endl;
    cout << mySqrt(2) << endl;
    cout << mySqrt(3) << endl;
    cout << mySqrt(4) << endl;
    cout << mySqrt(5) << endl;
    cout << mySqrt(6) << endl;
    cout << mySqrt(9) << endl;
}

