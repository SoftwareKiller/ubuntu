#include <iostream>

using namespace std;

//不是吧，阿sir，遍历也要挨打
double myPow_(double x, int n)
{
    if(n == 0)
        return 1.0f;
    double ret = x;
    if(n > 0)
    {
        for(int i = 1; i < n; ++i)
        {
            ret *= x;
        }
    }
    else
    {
        n = -n;
        for(int i = 1; i < n; ++i)
            ret *= x;
        ret = 1.0/ret;
    }

    return ret;
}

double myPow(double x, int n)
{
    if(n == 0)
        return 1.0f;
    if(x == 1.0f)
        return x;

    double ret = 1.0;

    long long N = n;
    bool flag = true;
    if(N < 0)
    {
        flag = false;
        N = -N;
    }

    double t = x;
    while(N > 0)
    {
        if(N & 0x1)
            ret *= t;
        t *= t;
        N = N >> 1;
    }

    if(!flag)
        ret = 1.0 / ret;

    return ret;
}

int main()
{
    cout << myPow(2.0, 10) << endl;
    cout << myPow(2.1, 3) << endl;
    cout << myPow(2.0, -2) << endl;
}

