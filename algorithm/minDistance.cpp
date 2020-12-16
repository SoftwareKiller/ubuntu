/*
 * 给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
 * 你可以对一个单词进行如下三种操作：
 * 1.插入一个字符
 * 2.删除一个字符
 * 3.替换一个字符
 * */

#include <iostream>
#include <string>

using namespace std;

int minDistance(string w1, string w2)
{
    int n = w1.length();
    int m = w2.length();

    if(m * n == 0) return m + n;

    int dp[n + 1][m + 1];

    for(int i = 0; i < n + 1; ++i)
        dp[i][0] = i;

    for(int i = 0; i < m + 1; ++i)
        dp[0][i] = i;

    for(int i = 1; i < n + 1; ++i)
    {
        for(int j = 1; j < m + 1; ++j)
        {
            int l = dp[i-1][j] + 1;
            int d = dp[i][j-1] + 1;
            int ld = dp[i-1][j-1];
            if(w1[i-1] != w2[j-1]) ld += 1;
            dp[i][j] = min(l, min(d, ld));
        }
    }

    return dp[n][m];
}

int main()
{
    cout << minDistance("horse", "ros") << endl;
    cout << minDistance("intention", "execution") << endl;
}

