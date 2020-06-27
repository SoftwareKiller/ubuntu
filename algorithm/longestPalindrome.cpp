#include <iostream>
#include <string>
#include <vector>

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
            if(end - start + 1 <= max) //这块进行一次剪枝，因为这种情况必不可能符合要求
                continue;
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


//动态规划求解
//状态转移方程：dp[i][j] = (s[i] == s[j]) and (j - 1 < 3 or dp[i+1][j-1])
string longestPalindrome(string s)
{
    int len = s.length();
    if(len < 2)
        return s;

    int max = 1;
    int start = 0;

    vector<vector<bool>> dp(len, vector<bool>(len));

    for(int i = 0; i < len; ++i)
    {
        dp[i][i] = true;
    }

    for(int j = 1; j < len; ++j)
    {
        for(int i = 0; i < len; ++i)
        {
            if(s[i] != s[j])
            {
                dp[i][j] = false;
            }
            else
            {//这里的所有情况s[i] == s[j]
                //s[i+1] == s[j-1]
                //(j-1)-(i+1) > 1
                //j - i > 3
                //一个字符认为是回文串
                if(j - i < 3)
                {
                    dp[i][j] = true;
                }
                else
                {
                    dp[i][j] = dp[i+1][j-1];
                }
            }

            if(dp[i][j] && j - i + 1 > max)
            {
                start = i;
                max = j - i + 1;
            }
        }
    }

    return s.substr(start, max);
}

int main()
{
    string s = "bab";
    cout << longestPalindrome_1(s) << endl;
    s = "cat";
    cout << longestPalindrome(s) << endl;
    s = "cbbd";
    cout << longestPalindrome_1(s) << endl;
    cout << longestPalindrome(s) << endl;
    s = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
    cout << longestPalindrome(s) << endl;
    cout << longestPalindrome(s) << endl;
}

