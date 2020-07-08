#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isValid(vector<string>& board, int row, int col)
{
    int n = board.size();
    //因为上下扫不到，故而需要单独扫当前皇后所在上下一列
    for(int i = 0; i < n; ++i)
    {
        if(board[i][col] == 'Q')
            return false;
    }

    for(int i = row - 1, j = col + 1; i >=0 && j < n; ++j, --i)
    {
        if(board[i][j] == 'Q')
            return false;
    }

    for(int i = row - 1, j = col - 1; i >=0 && j >= 0; --j, --i)
    {
        if(board[i][j] == 'Q')
            return false;
    }
    return true;
}

void backtrack(vector<vector<string>>& ret, vector<string>& board, int rows)
{
    if(board.size() == rows)
    {
        ret.push_back({board});
        return;
    }

    for(int col = 0; col < board.size(); ++col)
    {
        if(!isValid(board, rows, col))
            continue;

        board[rows][col] = 'Q';
        backtrack(ret, board, rows + 1);
        board[rows][col] = '.';
    }
}

vector<vector<string>> solveQueen(int n)
{
    vector<vector<string>> ret;
    vector<string> board(n, string(n, '.'));
    backtrack(ret, board, 0);
    return ret;
}

void print(vector<vector<string>>& v)
{
    for(auto& i : v)
    {
        for(auto&j : i)
            cout << j << "," << endl;
        cout << endl;
    }
    cout << v.size() << endl;
}

int main()
{
    auto ret = solveQueen(8);
    print(ret);
}

