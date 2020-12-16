#include <iostream>
#include <string>
#include <vector>

using namespace std;

//暴力终将挨打
int _longestValidParentheses(string s)
{
    int len = s.length();
    bool start = false;
    int max = 0;
    vector<char> st;
    for(int i = 0; i < len; ++i)
    {
        int sub = i;
        int cur = 0;
        for(; sub < len; ++sub)
        {
            if(s[sub] == '(')
            {
                st.push_back(s[sub]);
                continue;
            }
            if(!st.empty() && st.back() == '(' && s[sub] == ')')
            {
                cur += 2;
                st.pop_back();
                start = true;
            }
            else if(start)
            {
                start = false;
                max = max < cur ? cur : max;
                cur = 0;
                st.clear();
            }
        }
        max = max < cur ? cur : max;
    }

    return max;
}

/*
 * 确定状态：
 * 可以将i看作最后一个值
 * 1.s[i]
 *   1)s[i] == '('
 *       dp[i] = 0
 *   2)s[i] == ')'
 * 分情况讨论2)
 *   1.s[i-1] == '('
 *     dp[i] = dp[i-2] + 2
 *   2.s[i-1] == ')'
 *     dp[i] = dp[i-1] + 2
 *     && dp[i] = dp[i-1] + dp[i - dp[i-1] -2] +2
 * */
int longestValidParentheses(string s)
{
    int size = s.length();
    vector<int> dp(size, 0);
    int ret = 0;
    for(int i = 1; i < size; ++i)
    {
        //当遇到')'才开始计算
        if(s[i] == ')')
        {
            if(s[i-1] == '(')
            {
                dp[i] = 2;
                if(i - 2 >= 0)
                {
                    dp[i] = dp[i] + dp[i-2];
                }
            }
            else if(dp[i-1] > 0)
            {
                if((i - dp[i-1] -1) >= 0 && s[i - dp[i-1] -1] == '(')
                {
                    dp[i] = dp[i-1] + 2;
                    if((i - dp[i-1] - 2) >= 0)
                    {
                        dp[i] = dp[i] + dp[i - dp[i-1] -2];
                    }
                }
            }
        }
        ret = max(ret, dp[i]);
    }

    return ret;
}

int main()
{
    cout << longestValidParentheses("((()))") << endl;
    cout << longestValidParentheses("())") << endl;
    cout << longestValidParentheses("(()(()(") << endl;
    cout << longestValidParentheses(")()())") << endl;
    cout << longestValidParentheses("))))") << endl;
    cout << longestValidParentheses(")(()))))))") << endl;
}

