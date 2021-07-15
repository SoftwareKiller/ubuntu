#include <iostream>

using namespace std;

/*
 * 需要处理base和exponent各为正负的情况，以及为0的情况
 * 外层调用保证不同时为0
 * */

#define MIN_VALUE 1e-8

// 用于判断double类型是否为0，精度判断
#define IS_DOUBLE_ZERO(d)  (abs(d) < MIN_VALUE)

double Power(double base, int exponent) 
{   
    if(IS_DOUBLE_ZERO(base))
        return 0.0;

    // 指数为0返回1
    if(exponent == 0)
        return 1.0;

    double res = base;
    //用于判断正负的标记，正为true，负为false
    bool flag = true;

    if(exponent < 0)
        flag = false;
    // 指数取正
    exponent = abs(exponent);
    // 循环累乘
    for(int i = 1; i < exponent; ++i)
        res *= base;

    // 负数时，累乘值为分母
    if(!flag)
        res = 1/res;

    return res;
}

int main()
{
    cout << Power(2.000,3) << endl;
    cout << Power(2.100,3) << endl;
    cout << Power(2.000,-2) << endl;
    return 0;
}

