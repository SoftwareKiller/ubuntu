#include <iostream>
#include <vector>

using namespace std;

void print(vector<vector<int>>& v);

void rotate(vector<vector<int>>& matrix)
{
    int len = matrix.size(), l, r;
    //先延主对角线，就是左上到右下进行反转
    for(int i = 0; i < len; ++i)
    {
        for(int j = i; j < len; ++j)
        {
            swap(matrix[i][j], matrix[j][i]);
            print(matrix);
            cout << endl;
        }
    }
    cout << endl;
    //再左右反转
    for(int i = 0; i < len; ++i)
    {
        l = 0, r = len - 1;
        while(l < r)
        {
            swap(matrix[i][l++], matrix[i][r--]);
            print(matrix);
            cout << endl;
        }
    }
}

void print(vector<vector<int>>& v)
{
    for(auto& i : v)
    {
        for(auto& j : i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> v{{1,2,3},{4,5,6},{7,8,9}};
    //rotate(v);
    print(v);
    vector<vector<int>> f{{1,2},{3,4}};
    rotate(f);
    print(f);
}

