#include <iostream>
#include <string>
#include <climits>

using namespace std;

int Atoi(const char* str)
{
    if(str == nullptr)
        return 0;
    int ret = 0;
    bool minus = false;
    const char* num = str;
    while(*num)
    {
        if(*num == ' ')
        {
            ++num;
            continue;
        }
        if(*num == '-')
        {
            minus = true;
            ++num;
            continue;
        }
        if(*num >= '0' && *num <= '9')
        {
            int bit = *num - '0';
            ret = ret * 10 + bit;
            ++num;
        }
        else
            break;
    }

    if(minus)
        ret = 0 - ret;
    return ret;
}

int myAtoi(string str) {
    if(str.empty())
        return 0;

    int len = str.length();
    long long ret = 0;
    bool flag = true;
    bool start = false;
    for(int i = 0; i < len; ++i)
    {
        if(str[i] == ' ')
        {
            if(start)
                break;
            continue;
        }
        if(str[i] == '-')
        {
            if(start)
            {
                break;
            }
            flag = false;
            start = true;
            continue;
        }
        if(str[i] == '+')
        {
            if(start)
                break;
            start = true;
            continue;
        }

        start = true;
        if(str[i] >= '0' && str[i] <= '9')
        {
            int temp = str[i] - '0';
            if(ret * 10 + temp < INT_MAX)
            {
                ret = ret * 10 + temp;
            }
            else
            {
                ret = ret * 10 + temp;
                break;
            }
        }
        else
        {
            break;
        }
    }

    if(ret > INT_MAX && flag)
    {
        return INT_MAX;
    }

    if(!flag)
    {
        ret = 0 - ret;
        if(ret < INT_MIN)
        {
            return INT_MIN;
        }
    }

    return ret;
}

int main()
{
    char num1[] = "18";
    string s = num1;
    cout << Atoi(num1) << endl;
    cout << myAtoi(s) << endl;
    char num2[] = " 32 ";
    s = num2;
    cout << Atoi(num2) << endl;
    cout << myAtoi(s) << endl;
    char num3[] = "-19";
    s = num3;
    cout << Atoi(num3) << endl;
    cout << myAtoi(s) << endl;
    char num4[] = "38x";
    s = num4;
    cout << Atoi(num4) << endl;
    cout << myAtoi(s) << endl;
    char num5[] = "4193 with words";
    cout << Atoi(num5) << endl;
    s = "4193 with words";
    cout << myAtoi(s) << endl;
    s = "+-2";
    cout << myAtoi(s) << endl;
    return 0;
}

