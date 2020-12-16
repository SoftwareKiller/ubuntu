#include <iostream>
#include <vector>
#include <string>

using namespace std;

void recursion(vector<string>& ret, string s, int n, string ip)
{
    if(n == 4)
    {
        if(s.empty()) ret.push_back(ip);
    }
    else
    {
        for(int k = 1; k < 4; ++k)
        {
            if(s.size() < k) break;
            int val = stoi(s.substr(0, k));
            if(val > 255 || k != to_string(val).size())
                continue;
            recursion(ret, s.substr(k), n + 1, ip + s.substr(0, k) + (n == 3 ? "" : "."));
        }
    }
}

vector<string> restoreIpAddressed(string s)
{
    if(s.empty() || s.length() > 12 || s.length() < 4)
        return {};
    vector<string> ret;
    string ip;
    recursion(ret, s, 0, ip);
    return ret;
}

void print(vector<string>& v)
{
    for(auto& i: v)
        cout << i << endl;
}

int main()
{
    auto ret = restoreIpAddressed("25525511135");
    print(ret);
}

