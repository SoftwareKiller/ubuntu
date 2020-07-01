#include <iostream>
#include <string>

using namespace std;

int strStr(string str, string needle)
{
    if(needle.empty()) return 0;

    int len = str.length(), sublen = needle.length();
    int start = 0, end = 0;
    for(int i = 0; i < len;)
    {
        if(str[i] == needle[0] && len - i >= sublen && str[i+sublen-1] == needle[sublen-1])
        {
            start = i;
            for(; end < sublen; )
            {
                if(str[i] == needle[end])
                {
                    ++i, ++end;
                }
                else
                    break;
            }

            if(end == sublen)
                return start;
            else
            {
                i = start, end = 0;
            }
        }
        ++i;
    }

    return -1;
}

int main()
{
    string s{"hello"};
    string n("h");
    cout << strStr(s, n) << endl;
}

