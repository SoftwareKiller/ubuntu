/*
 * 将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
 * 比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
 * L   C   I   R
 * E T O E S I I G
 * E   D   H   N
 * 来源：力扣（LeetCode）
 * */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//自己码的，和官方思想差不多，但是有一个案例过不了，本地是可以过的
//不过编码风格就有点臭了
string convert_(string s, int numRows)
{
    if(numRows < 2 || s.empty())
        return s;

    int len = s.length();
    vector<string> arr(numRows);
    string ret = "";

    int row = 0;
    bool flag = false;
    bool end = true;
    for(int i = 0; i < len;)
    {
        for(int j = 0; j < numRows; ++j)
        {
            if(flag)
            {
                if(j == row)
                {
                    arr[j] += s[i++];
                    --row;
                }
                if(!row)
                {
                    flag = false;
                    break;
                }
                continue;
            }
            /*else
            {
                if(flag && j + 1 == numRows)
                    flag = false;
                if(flag)
                    continue;
            }*/
            if(j + 1 == numRows)
                end = true;
            arr[j] += s[i++];
        }
        if(end)
        {        
            flag = true;
            row = numRows - 2;
            end = false;
        }
    }

    for(int i = 0; i < numRows; ++i)
    {
        ret += arr[i];
    }

    return ret;
}

//看完官方的代码写的
string convert(string s, int numRows)
{
    if(s.empty() || numRows < 2)
        return s;

    int len = s.length();
    vector<string> rows(numRows);
    int curr_row = 0;
    bool lf = false; //是否换行

    for(char c : s)
    {
        rows[curr_row] += c;

        if(curr_row == 0 || curr_row == numRows - 1) //只在靠近上下边界的地方切换换行状态
        {
            lf = !lf;
        }

        curr_row += lf ? 1 : -1;
    }

    string ret;
    for(auto& str : rows)
        ret += str;

    return ret;
}

int main()
{
    string s{"LEETCODEISHIRING"};
    cout << convert(s, 3) << endl;
    cout << convert(s, 4) << endl;
    s = "PAYPALISHIRING";

    cout << convert(s, 4) << endl;
}

