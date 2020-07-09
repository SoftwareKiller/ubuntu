#include <iostream>
#include <vector>

using namespace std;

void generateSubMatrix(vector<vector<int>>& ret, int lo, int hi, int& count)
{
    int l = lo, r = hi;
    for(int i = l; i <= r; ++i)
        ret[lo][i] = count++;

    for(int i = lo + 1; i <= hi; ++i)
        ret[i][r] = count++;

    for(int i = r - 1; i >= l; --i)
        ret[hi][i] = count++;

    for(int i = hi - 1; i >= lo + 1; --i)
        ret[i][l] = count++;
}

vector<vector<int>> generateMatrix(int n)
{
    if(n <= 0)
        return {};

    vector<vector<int>> ret(n, vector<int>(n, 0));

    int count = 1;
    int start = 0, end = n - 1;
    while(start <= end)
    {
        generateSubMatrix(ret, start++, end--, count);
    }

    return ret;
}

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(auto&j : i)
            cout << j << ", ";
        cout << endl;
    }
}

int main()
{
    auto ret = generateMatrix(1);
    print(ret);
    ret = generateMatrix(2);
    print(ret);
    ret = generateMatrix(3);
    print(ret);
    ret = generateMatrix(4);
    print(ret);
}

