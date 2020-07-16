#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool recursion(string s1, string s2)
{
    if(s1 == s2)
        return true;
    if(s1.size() != s2.size()) return false;

    string t1 = s1, t2 = s2;
    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());

    if(t1 != t2) return false;

    for(int i = 1; i < s1.size(); ++i)
    {
        if((recursion(s1.substr(0, i), s2.substr(0, i)) && recursion(s1.substr(i, s1.size() - i), s2.substr(i, s2.size() - i)))
           || (recursion(s1.substr(0, i), s2.substr(s2.size() - i, i)) && recursion(s1.substr(i, s1.size() - i), s2.substr(0, s2.size() - i))))
            return true;
    }
    return false;
}

bool isScramble(string s1, string s2)
{
    if(s1.size() != s2.size())
        return false;
    return recursion(s1, s2);
}

int main()
{
    cout << isScramble("great", "rgeta") << endl;
}

