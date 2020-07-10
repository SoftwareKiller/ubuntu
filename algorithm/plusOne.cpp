#include <iostream>
#include <vector>

using namespace std;

vector<int> _plusOne(vector<int>& v)
{
    if(v.empty()) return {};

    int n = v.size();
    bool flag = false;
    bool update = false;
    for(int i = n - 1; i >= 0; --i)
    {
        if(v[i] < 9)
        {
            if(!update)
                ++v[i];
            flag = true;
            break;
        }
        else if(i > 0)
        {
            v[i] = 0;
            v[i-1]++;
            if(v[i-1] < 10)
            {
                flag = true;
                break;
            }
            update = true;
            if(i-1 == 0 && v[i-1] < 10) flag = true;
        }
    }

    if(flag)
        return {v};

    vector<int> ret{1};
    v[0] = 0;
    for(int i = 0; i < n; ++i)
        ret.push_back(v[i]);

    return ret;
}

//别人的骚方法
vector<int> plusOne(vector<int>& v)
{
    if(v.empty()) return {};

    for(int i = v.size() - 1; i >= 0; --i)
    {
        if(v[i] == 9)
            v[i] = 0;
        else
        {
            ++v[i];
            return {v};
        }
    }

    if(v[0] == 0) v[0] = 1;
    v.push_back(0);
    return {v};
}

void print(vector<int>& v)
{
    for(auto i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v{9,9};
    auto ret = plusOne(v);
    print(ret);
}

