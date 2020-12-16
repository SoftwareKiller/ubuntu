#include <iostream>
#include <vector>

using namespace std;

void setZero(vector<vector<int>>& m, vector<int>& pos)
{
    for(int i = 0; i < pos.size(); ++i)
    {
        for(int j = 0; j < m.size(); ++j)
        {
            m[j][pos[1]] = 0;
        }

        for(int j = 0; j < m[0].size(); ++j)
        {
            m[pos[0]][j] = 0;
        }
    }
}

void setZeroes(vector<vector<int>>& m)
{
    vector<vector<int>> pos;
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m[0].size(); ++j)
        {
            if(m[i][j] == 0)
                pos.push_back({i,j});
        }
    }

    for(int i = 0; i < pos.size(); ++i)
    {
        setZero(m, pos[i]);
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
    vector<vector<int>> v{{1,1,1}, {1,0,1},{1,1,1}};
    setZeroes(v);
    print(v);
}

