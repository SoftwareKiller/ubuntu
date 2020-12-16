#include <vector>
#include <iostream>

using namespace std;

int uniquePathWithObstacles_(vector<vector<int>>& v)
{
    if(v.empty()) return 0;

    int n = v.size(), m = v[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int i = 0; i < m; ++i)
    {
        if(v[0][i] == 1) break;
        dp[0][i] = 1;
    }

    for(int i = 0; i < n; ++i)
    {
        if(v[i][0] == 1) break;
        dp[i][0] = 1;
    }

    for(int i = 1; i < n; ++i)
    {
        for(int j = 1; j < m; ++j)
        {
            if(v[i][j] == 1) dp[i][j] = 0;
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[n-1][m-1];
}

int uniquePathWithObstacles(vector<vector<int>>& v)
{
    if(v.empty()) return 0;
    int n = v.size(), m = v[0].size();
    vector<int> f(m);

    f[0] = v[0][0] == 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(v[i][j] == 1)
            {
                f[j] = 0;
                continue;
            }
            if(j - 1 >= 0 && v[i][j-1] == 0)
                f[j] += f[j-1];
        }
    }

    return f[m-1];
}
int main()
{
    vector<vector<int>> v{{0,0,0},{0,1,0},{0,0,0}};
    cout << uniquePathWithObstacles(v) << endl;
}

