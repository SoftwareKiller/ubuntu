/*
 * 将字符串中的空格替换为%20
 * */
#include <iostream>
#include <cstring>

using namespace std;

void replaceSpace(char* str, int length)
{
    if(str == NULL || length <= 0)
        return;

    int count = 0;
    char* temp = str;
    while(*temp)
    {
        if(*temp == ' ')
            ++count;
        ++temp;
    }

    int len = strlen(str);
    int newlen = len + count * 2;
    while(len >= 0 && newlen > len)
    {
        if(str[len] == ' ')
        {
            str[newlen--] = '0';
            str[newlen--] = '2';
            str[newlen--] = '%';
        }
        else
        {
            str[newlen--] = str[len];
        }
        --len;
    }
}

int main()
{
    char str1[32] = "Hello world";
    char str2[32] = " HelloWodld";
    char str3[32] = "HelloWorld ";
    replaceSpace(str1, 32);
    replaceSpace(str2, 32);
    replaceSpace(str3, 32);

    cout << str1 << "  " << str2 << "  " << str3 << endl;
    return 0; 
}

