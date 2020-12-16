#include <iostream>
#include <string>
#include <vector>

using namespace std;

int numDecodings_(string s)
{
    if(s.empty()) return 0;

   int count = 1;
    for(int i = 1; i < s.size(); ++i)
    {
        if(s[i-1] < '3' && s[i] <= '6')
            ++count;
    }

    return count;
}

int numDecodings__(string s)
{
    if(s.empty()) return 0;

    vector<int> dp(s.length() + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 1; i < s.size(); ++i)
    {
        if(s[i] == '0')
        {
            if(s[i-1] == '1' || s[i-1] == '2')
                dp[i+1] = dp[i-1];
            else
                return 0;
        }
        else
        {
            if(s[i-1] == '1' || (s[i-1] == '2' && s[i] >= '1' && s[i] <= '6'))
                dp[i+1] = dp[i-1] + dp[i];
            else
                dp[i+1] = dp[i];
        }
        cout << dp[i] << " ";
    }

    return dp[s.length()];
}

int numDecodings(string s)
{
    if(s.empty() || s[0] == '0') return 0;

    int curr = 1, pre = 1;
    for(int i = 1; i < s.size(); ++i)
    {
        int temp = curr;
        if(s[i] == '0')
        {
            if(s[i-1] == '1' || s[i-1] == '2')
                curr = pre;
            else
                return 0;
        }
        else if(s[i-1] == '1' || (s[i-1] == '2' && s[i] >= '1' && s[i] <= '6'))
            curr = curr + pre;
        pre = temp;
    }

    return curr;
}

int main()
{
    cout << numDecodings__("12") << endl;
    cout << numDecodings__("226") << endl;
    cout << numDecodings__("221916") << endl;
}

