#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool backtrace(vector<vector<char>>& board, string word, int index, int x, int y)
{
    if(board[x][y] != word[index])
        return false;

    if(word.size()-1 == index)
        return true;

    char c = board[x][y];
    board[x][y] = 0;
    ++index;

    if((x > 0 && backtrace(board, word, index, x - 1, y))
        || (y > 0 && backtrace(board, word, index, x, y - 1))
        || (x < board.size() - 1 && backtrace(board, word, index, x + 1, y))
        || (y < board[0].size() - 1 && backtrace(board, word, index, x, y + 1)))
        return true;

    board[x][y] = c;
    return false;
}

bool exist(vector<vector<char>>& board, string word)
{
    int index = 0;
    for(int i = 0; i < board.size(); ++i)
    {
        for(int j = 0; j < board[0].size(); ++j)
        {
            if(board[i][j] == word[index])
            {
                if(backtrace(board, word, index, i, j))
                    return true;
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<char>> board{{'A','B','C','E'},
                               {'S','F','C','S'},
                               {'A','D','E','E'}};
    string word = "SEC";
    cout << exist(board, word) << endl;
}

