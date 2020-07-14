#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

//可以多，不能少
bool check(unordered_map<char, int>& hash, unordered_map<char, int>& cnt)
{
    for(const auto& p : hash)
        if(cnt[p.first] < p.second)
            return false;
    return true;
}

string minWindow(string s, string t)
{
    unordered_map<char,int> hash, cnt;
    for(auto& c : t)
        hash[c]++;

    int l = 0, r = -1;
    int min = INT_MAX, start = -1;
    while(r < static_cast<int>(s.length()))
    {
        if(hash.find(s[++r]) != hash.end())
            ++cnt[s[r]];

        while(check(hash, cnt) && l <= r)
        {
            if(r - l + 1 < min)
            {
                min = r - l + 1;
                start = l;
            }

            if(hash.find(s[l]) != hash.end())
                --cnt[s[l]];
            ++l;
        }
    }

    return start == -1 ? "" : s.substr(start, min);
}

int main()
{
    cout << minWindow("ADOBECODEBANC", "ABC") << endl;
}

