#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//复杂的咱也没看懂，遇事不决，暴力解决
vector<int> findSubstring(string s, vector<string>& v)
{
    if (v.empty()) return {};
    unordered_map<string, int> hash;
    for (auto& i : v)
        hash[i]++;

    int right = s.length();
    int step = v[0].length();
    vector<int> ret;
    unordered_map<string, int> res;
    bool flag = false;
    int start = 0;
    for (int i = 0; (i + step) <= right;)
    {
        string sub = s.substr(i, step);
        auto it = hash.find(sub);
        if (it != hash.end() && ((right - start) >= step * v.size())) //稍微加个剪枝
        {
            res[it->first]++;
            if (!flag)
                start = i;
            flag = true;
            i += step;
            if (res == hash || res[it->first] > hash[it->first])
            {
                if (res == hash)
                    ret.push_back(start);
                i = start + 1;
                flag = false;
                res.clear();
            }
            continue;
        }
        else if(flag)
        {
            i = start;
            flag = false;
            res.clear();
        }
        ++i;
    }

    return ret;
}

void print(vector<int>& v)
{
    cout << "[ ";
    for(auto& i : v)
        cout << i << " ";
    cout << "]" << endl;
}

int main()
{
    vector<string> v{"foo", "bar"};
    string str{"barfoothefoobarman"};
    auto ret = findSubstring(str, v);
    print(ret);
}

