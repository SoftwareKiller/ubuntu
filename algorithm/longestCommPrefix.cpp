#include <iostream>
#include <string>
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs)
{
    if(strs.empty())
    {
        return {};
    }
    string s = "";
    char c = ' ';
    int len = strs.size();
    int count = 0;
    while(true)
    {
        int i = 0;
        c = strs[i][count];
        for(; i < len; ++i)
        {
            if(strs[i].length() > count)
            {
                if(c != strs[i][count])
                    return s;
            }
            else
                return s;
        }
        s += c;
        ++count;
    }

    return s;
}

int main()
{
    vector<string> v{"flower","flow","flight"};
    cout << longestCommonPrefix(v) << endl;
}

