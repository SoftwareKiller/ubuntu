#include <iostream>
#include <vector>

using namespace std;

//终于不看答案凭本事做出dp了，暴风哭泣
//
//在上面选择的路径中找出最小的，第一行和第一列都是累加
//下面的路径选择子路径中最小的路径
//dp[i][j] = dp[i-1][j] <= dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
//然后加上当前位置的权重
int minPathSum(vector<vector<int>>& v)
{
    if(v.empty())
        return 0;

    int n = v.size(), m = v[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(i == 0 && j == 0)
                dp[i][j] = v[i][j];
            else if(i == 0)
                dp[i][j] = dp[i][j-1] + v[i][j];
            else if(j == 0)
                dp[i][j] = dp[i-1][j] + v[i][j];
            else
            {
                dp[i][j] = dp[i-1][j] <= dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
                dp[i][j] += v[i][j];
            }
        }
    }

    return dp[n-1][m-1];
}

int main()
{
    vector<vector<int>> v{{1,2}, {3,1}};
    cout << minPathSum(v) << endl;
}

