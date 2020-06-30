#include <iostream>
#include <string>
#include <vector>

using namespace std;

void backtrack(vector<string>& ret, string& s, int open, int close, int n)
{
    if(s.length() == n * 2)
    {
        ret.push_back(s);
        return;
    }

    if(open < n)
    {
        s.push_back('(');
        backtrack(ret, s, open + 1, close, n);
        s.pop_back();
    }

    if(close < open)
    {
        s.push_back(')');
        backtrack(ret, s, open, close + 1, n);
        s.pop_back();
    }
    
}

vector<string> generateParenthesis(int n)
{
    vector<string> ret;

    string s;
    backtrack(ret, s, 0, 0, n);
    return ret;
}

void print(vector<string> v)
{
    for(auto& s : v)
    {
        cout << s << endl;
    }
}

int main()
{
    print(generateParenthesis(2));
    print(generateParenthesis(3));
}

