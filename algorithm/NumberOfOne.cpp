//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
#include <iostream>

int NumerOfOne(int n)
{
    if(!n)
        return 0;
    int count = 0;
    while(n != 0)
    {
        ++count;
        n = n & (n - 1);
    }
    return count;
}

int main()
{
    using namespace std;
    cout << NumerOfOne(10) << endl;
    cout << NumerOfOne(100) << endl;
    cout << NumerOfOne(7) << endl;
    cout << NumerOfOne(-1) << endl;
    cout << NumerOfOne(-2147) << endl;
    return 0;
}

