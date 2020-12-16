#include <iostream>

using namespace std;

//斐波那契
//用dp的方式思考，前两个台阶的跳法之和等于当前台阶的跳法数
int climbStairs(int n)
{
    if(n < 3)
        return n;

    int dp[3] = {1, 2, 3};
    for(int i = 2; i < n; ++i)
    {
        int temp = dp[2];
        dp[0] = dp[1];
        dp[1] = temp;
        dp[2] = dp[1] + dp[0];
    }

    return dp[2];
}

int main()
{
    cout << climbStairs(1) << endl;
    cout << climbStairs(2) << endl;
    cout << climbStairs(3) << endl;
    cout << climbStairs(4) << endl;
    cout << climbStairs(5) << endl;
    cout << climbStairs(6) << endl;
    cout << climbStairs(7) << endl;
}

