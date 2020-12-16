#include <iostream>
#include <vector>
#include <unordered_map>
/*
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 根据手机九宫格
 * */
using namespace std;

//回溯大法好，递归保平安
vector<string> letterCombiantions(string digits)
{
    static unordered_map<char, string> dict{{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, 
        {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

    if(digits.length() > 1)
    {
        auto sub = letterCombiantions(digits.substr(1, digits.length()-1));
        vector<string> ret;
        auto it = dict.find(digits[0]);
        if(it != dict.end())
        {
            for(auto s : it->second)
            {
                for(auto substr_ : sub)
                {
                    ret.push_back(s + substr_);
                }
            }
        }

        return ret;
    }
    else
    {
        vector<string> ret;
        auto it = dict.find(digits[0]);
        if(it != dict.end())
        {
            for(auto s : it->second)
            {
                ret.push_back(string(1, s));
            }
        }

        return ret;
    }
}

void printResult(vector<string> s)
{
    for(auto& it : s)
    {
        cout << it << endl;
    }
}

int main()
{
    string s{"2349"};
    printResult(letterCombiantions(s));
}

