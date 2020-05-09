#include <iostream>

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

int main()
{
    char num1[] = "18";
    cout << Atoi(num1) << endl;
    char num2[] = " 32 ";
    cout << Atoi(num2) << endl;
    char num3[] = "-19";
    cout << Atoi(num3) << endl;
    char num4[] = "38x";
    cout << Atoi(num4) << endl;
    return 0;
}

