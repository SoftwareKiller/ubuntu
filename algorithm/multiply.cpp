#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void mul(string& n1, int n2, int bit)
{
    int len = n1.length();
    int temp = 0;
    int i;
    for(i = len - 1 - bit; i >= 0; --i)
    {
        int ans = n1[i] - '0';
        if(temp > 0)
        {
            temp = temp + ans * n2;
        }
        else
            temp = ans * n2;
        const char* c = to_string(temp % 10).c_str();
        n1[i] = *c;
        temp /= 10;
        cout << n1 << " ";
    }
    if(temp > 0)
    {
        n1 = to_string(temp) + n1;
    }
}

//好吧，只能乘个位，考虑不周全
string multiply_(string n1, string n2)
{
    if(n1.empty() || n2.empty() || n1[0] == '0' || n2[0] == '0')
        return "0";

    int len = n2.length();
    for(int i = len - 1; i >= 0; --i)
    {
        if(n2[i] == '0')
        {
            n1 += "0";
            continue;
        }
        mul(n1, n2[i] - '0', len - i - 1);
    }
    return n1;
}


string multiply(string n1, string n2)
{
    if(n1.empty() || n2.empty() || n1[0] == '0' || n2[0] == '0')
        return "0";

    //正向写高位进位需要搬移，不如直接反转
    reverse(n1.begin(), n1.end());
    reverse(n2.begin(), n2.end());
    int l1 = n1.size(), l2 = n2.size();

    vector<int> v(l1 + l2, 0);
    for(int i = 0; i < l1; ++i)
    {
        for(int j = 0; j < l2; ++j)
        {
            v[i + j] += (n1[i] - '0')*(n2[j] - '0');
        }
    }

    for(int i = 0; i < l1 + l2; ++i)
    {
        if(v[i] > 9)
        {
            int t = v[i];
            v[i] = t % 10;
            v[i + 1] += t/10;
        }
    }

    int pos = (v[l1 + l2 - 1] == 0 ? l1 + l2 - 2 : l1 + l2 - 1);
    string ret = "";
    for(; pos >= 0; --pos)
    {
        ret += (v[pos] + '0');
    }

    return ret;
}

int main()
{
    cout << multiply("123", "19") << endl;
}

