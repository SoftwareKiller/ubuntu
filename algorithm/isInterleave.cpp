#include <iostream>
#include <string>
#include <vector>

using namespace std;

//索引扫描，当相同时会出错，故此种解法错误
bool isInterleave_(string s1, string s2, string s3)
{
    int m = s1.length(), n = s2.length(), t = s3.length();

    if(m + n != t)
        return false;

    int i = 0, j = 0, k = 0;

    while(k < t)
    {
        if(i < m && s1[i] == s3[k])
            ++i;
        else if(j < n && s2[j] == s3[k])
            ++j;
        else
            return false;
        ++k;
    }

    return true;
}

bool isInterleave(string s1, string s2, string s3)
{
    vector<int> dp(s2.size() + 1, false);

    int n = s1.length(), m = s2.length(), t = s3.length();

    if(m + n != t)
        return false;

    dp[0] = true;
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= m; ++j)
        {
            int p = i + j - 1;
            if(i > 0)
            {
                dp[j] &= (s1[i - 1] == s3[p]);
            }
            if(j > 0)
            {
                dp[j] |= (dp[j - 1] && s2[j - 1] == s3[p]);
            }
        }
    }

    return dp[m];
}

int main()
{
    cout << isInterleave_("aabcc", "dbbca", "aadbbcbcac") << endl;
}

