#include <cstring>
#include <iostream>
#include <string>
#include <vector>


/*
 * 正则表达式匹配.*两个符号
 * */

using namespace std;

/*
 * 用状态机太复杂，解题失败，还是得动态规划
 * */
bool isMatch_(string s, string p)
{
    int m = s.length();
    int n = p.length();

    int i = 0, j = 0;
    char star = '*', point = '.';
    enum STATUS{
        MATCH_ONE,
        MATCH_ALL,
        NOT_MATCH
    };
    STATUS status = NOT_MATCH;
    pair<STATUS, char> match_char{NOT_MATCH, ' '};
    while(i < m && j < n)
    {
        if(s[i] == p[j] || p[j] == point)
        {
            ++i, ++j;
            match_char.first = MATCH_ONE;
            match_char.second = s[i];
            continue;
        }

        if(s[i] == match_char.second && p[j] == star)
        {
            ++i;
            match_char.first = MATCH_ALL;
            continue;
        }
        else if(p[j] == star)
        {
            ++j;
            match_char.first = NOT_MATCH;
            match_char.second = ' ';
            continue;
        }
    }
    if(i < m)
        return false;

    return true;
}

void printResult(bool flag)
{
    if(flag)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

//官方版本
bool _isMatch(string s, string p)
{
    int m = s.length();
    int n = p.length();

    auto matchs = [&](int i, int j)
    {
        if(i == 0)
            return false;
        if(p[j - 1] == '.')
            return true;

        return s[i - 1] == p[j - 1];
    };

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    dp[0][0] = true;
    for(int i = 0; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(p[j - 1] == '*')
            {
                //这是为了aab, aabc*这种情况，true
                dp[i][j] |= dp[i][j - 2];
                if(matchs(i, j - 1))
                {
                    dp[i][j] |= dp[i - 1][j];
                }
            }
            else
            {
                if(matchs(i, j))
                {
                    dp[i][j] |= dp[i - 1][j - 1];
                }
            }
        }
    }

    return dp[m][n];
}


//一个稍微好理解一点点的版本
//
/*
 * dp[i][j]表示s的前i个是否能被p的前j个匹配
 * 1.最简单的思路，前面的完全匹配，则dp[i][j]匹配
 *     dp[i][j] = dp[i-1][j-1]
 * 2.但是p[j]可能等于"."和"*"，还有各种符号
 *   2.1  p[j] == '.'
 *     dp[i][j] == dp[i-1][j-1]
 *   2.2  p[j] == '*'
 *        列入情况3讨论
 *
 * 3.'*'的意思是匹配*号的前一个字符，数量零个到多个都可，注意是零个
 *   3.1 '*'号前是零个匹配：abc 和 abcd*是匹配的，有零个d
 *     dp[i][j] = dp[i][j-2]
 *   3.2 '*'号前有一个匹配
 *     dp[i][j] = dp[i][j-1]
 *   3.3 '*'号前有多个匹配
 *     dp[i][j] = dp[i-1][j]
 * */
bool isMatch(string s, string p)
{
    s = " " + s;
    p = " " + p;
    int m = s.size(), n = p.size();

    bool dp[m + 1][n + 1];
    memset(dp, false, (m+1)*(n+1));
    dp[0][0] = true;  //最小子集为真，因为都是space
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <=n; ++j)
        {
            //对应情况1和2.1
            if(s[i - 1] == p[j - 1] || p[j - 1] == '.')
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else if(p[j - 1] == '*')  //对应情况3
            {
                if(s[i - 1] != p[j - 2] && p[j - 2] != '.')
                {
                    //处理如：aab和c*a*b
                    dp[i][j] = dp[i][j - 2];
                }
                else
                {
                    //对应情况3.1----3.3
                    dp[i][j] = dp[i][j - 1] || dp[i][j - 2] || dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}

int main()
{
    string s{"aa"};
    string p{".*"};
    printResult(isMatch(s, p));
    s = "aab";
    p = "c*a*b";
    printResult(isMatch(s, p));
    s = "aaaa";
    p = "a*";
    printResult(isMatch(s, p));
    s = "mississippi";
    p = "mis*is*p*.";
    printResult(isMatch(s, p));
    s = "aaaaabc";
    p = "c*b*a*bc";
    printResult(isMatch(s, p));
}

