#include <iostream>
#include <string>

using namespace std;

bool isInt(const char** cur)
{
    const char* c = *cur;
    bool flag = false;
    //只要有一个数字，那就认为是数字，剩下的事情，交给后面
    while(*c >= '0' && *c <= '9')
    {
        ++c;
        flag = true;
    }
    *cur = c;

    return flag;
}

bool isSymbol(const char** cur)
{
    const char* c = *cur;
    if(*c == '-' || *c == '+')
        ++c;
    *cur = c;

    return isInt(cur);
}

bool isNumber(string s)
{
    if(s.empty()) return false;

    /*int len = 0;
    for(int i = s.length() - 1; i >= 0; --i)
    {
        if(s[i] == ' ') ++len;
        else
            break;
    }
    s = s.substr(0, s.length() - len);
    len = 0;
    for(int i = 0; i < s.length(); ++i)
    {
        if(s[i] == ' ') ++len;
        else
            break;
    }
    s = s.substr(len);*/
    int i = 0;
    for(; i < s.length(); ++i)
    {
        if(s[i] == ' ') ;
        else
            break;
    }
    s = s.substr(i);
    for(i = s.length() - 1; i >= 0; --i)
    {
        if(s[i] == ' ') ;
        else
            break;
    }
    s = s.substr(0, i + 1);

    if(s.empty()) return false;

    const char* c = s.c_str();

    bool isNum = isSymbol(&c);

    if(*c == '.')
    {
        ++c;
        isNum = isNum | isInt(&c);
    }

    if(*c == 'e' || *c == 'E')
    {
        ++c;
        isNum = isNum & isSymbol(&c);
    }

    return isNum & (*c == '\0');
}

int main()
{
    cout << isNumber("0 ") << endl;
    cout << isNumber("0.1") << endl;
    cout << isNumber("1 a") << endl;
}

