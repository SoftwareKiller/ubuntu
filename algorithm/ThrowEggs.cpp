#include <iostream>
#include <algorithm>

using namespace std;

int record[512][512] = {0};

//k为楼层高度
//n为鸡蛋剩余数量
int throwEggs(int k, int n)
{
    if(n == 1)
        return k;
    if(k == 0)
        return 0;
    if(record[k][n])
        return record[k][n];

    int res = k;
    int lo = 1, hi = k;
    while(lo <= hi)
    {
        int mid = (hi + lo)/2;
        int broken = throwEggs(mid - 1, n - 1); //碎了
        int not_broken = throwEggs(k - mid, n); //没碎
        if(broken > not_broken)
        {
            hi = mid - 1;
            res = min(res, broken + 1);
        }
        else
        {
            lo = mid + 1;
            res = min(res, not_broken + 1);
        }
    }
    record[k][n] = res;
    return res;
}

int main()
{
    cout << throwEggs(100, 2) << endl;
}

