#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValid(string s)
{
    stack<char> sa;
    int n = s.length();
    if(n % 2 == 1)
        return false;
    int i = 1;
    sa.push(s[0]);

    typedef  pair<char, char> Node;
    Node k1{')', '('};
    Node k2{'}', '{'};
    Node k3{']', '['};
    while(!sa.empty() && i < n)
    {
        if(s[i] == k1.second || s[i] == k2.second || s[i] == k3.second)
        {
            sa.push(s[i]);
            ++i;
        }
        else if(s[i] == k1.first || s[i] == k2.first || s[i] == k3.first)
        {
            char top = sa.top();
            if(s[i] == k1.first && top == k1.second)
            {
                sa.pop();
                ++i;
                continue;
            }
            else if(s[i] == k2.first && top == k2.second)
            {
                sa.pop();
                ++i;
                continue;
            }
            if(s[i] == k3.first && top == k3.second)
            {
                sa.pop();
                ++i;
                continue;
            }
            return false;
        }
    }

    if(!sa.empty())
        return false;
    return true;
}

void print(bool flag)
{
    if(flag)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

int main()
{
    print(isValid("()"));
    print(isValid("(){}[]"));
    print(isValid("(]"));
    print(isValid("([)]"));
    print(isValid("{[]}"));
}

