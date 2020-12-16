#include <iostream>
#include <vector>

using namespace std;

int uniquePaths(int m, int n)
{
    if(m <= 0 || n <= 0)
        return 0;
    if(m < 2 || n < 2)
        return 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][1] = 1;
    dp[1][0] = 1;

    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}

int main()
{
    cout << uniquePaths(7, 3) << endl;
}

