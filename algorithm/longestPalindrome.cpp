#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isPalindrome(int start, int end, string& s)
{
    while(start < end)
    {
        if(s[start] == s[end])
        {
            ++start;
            --end;
        }
        else
            break;
    }
    if(start >= end)
        return true;
    return false;
}

//暴力求解,O(n^3)
string longestPalindrome_1(string s)
{
    if(s.empty())
        return s;

    int n = s.size();
    int max = 1;
    pair<int, int> pos;
    for(int start = 0; start < n; ++start)
    {
        for(int end = start; end < n; ++end)
        {
            bool flag = isPalindrome(start, end, s);
            if(flag)
            {
                if(end - start + 1 > max)
                {
                    max = end - start + 1;
                    pos.first = start;
                    pos.second = end;
                }
            }
        }
    }

    return s.substr(pos.first, max);
}

int main()
{
    string s = "bab";
    cout << longestPalindrome_1(s) << endl;
    s = "cbbd";
    cout << longestPalindrome_1(s) << endl;
    s = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
    cout << longestPalindrome_1(s) << endl;
}

