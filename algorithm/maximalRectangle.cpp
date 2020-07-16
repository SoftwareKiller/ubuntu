#include <iostream>
#include <vector>

using namespace std;

int maximalRectangle(vector<vector<char>>& matrix)
{
    int n = matrix.size();
    int m = 0;
    if(n > 0)
        m = matrix[0].size();

    vector<vector<int>> height(n + 1, vector<int>(m + 1, 0));
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
    int ret = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(matrix[i-1][j-1] == '0')
                continue;
            height[i][j] = height[i-1][j] + 1;
            for(int k = 1; k <= height[i][j]; ++k)
            {
                dp[i][j][k] = dp[i][j-1][k] + k;
                ret = max(ret, dp[i][j][k]);
            }
        }
    }

    return ret;
}

int main()
{
    vector<vector<char>> v{{'1','0','1','0','0'},
                           {'1','0','1','1','1'},
                           {'1','1','1','1','1'},
                           {'1','0','0','1','0'}};
    cout << maximalRectangle(v) << endl;
}

