#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

//整数除法
int divide(int dividend, int divisor)
{
    if(dividend == 0 || divisor == 0) return 0;
    bool sign = (dividend ^ divisor) >= 0;  //异或符号位判断正负，相同为0，是正数或0
    if(dividend > 0) dividend = -dividend;
    if(divisor > 0) divisor = -divisor;     //取负可以防溢出

    int ret = 0;
    int count = -1;
    int temp = dividend, divtemp = divisor;

    while(divtemp > ((unsigned int)INT_MIN >> 1 | 0x80000000) && (temp <= ((unsigned int)divtemp << 1)))
    {
        divtemp <<= 1;
        temp -= divtemp;
        count <<= 1;
        ret += count;
    }

    while(temp <= divisor)
    {
        if(temp <= divtemp)
        {
            temp -= divtemp | 0x80000000;
            ret += count | 0x80000000;
        }
        else if(((unsigned int)divtemp >> 1 | 0x80000000) <= divisor)
        {
            divtemp >>= 1;
            count >>= 1;
        }
    }

    if(sign)
    {
        if(ret == INT_MIN)
            return INT_MAX;
        return -ret;
    }

    return ret;
}

int main()
{
    cout << divide(9, 3) << endl;
    cout << divide(434343421, 3) << endl;
    cout << divide(313213 ,32131321) << endl;
    cout << divide(-32342321, 3) << endl;
}

