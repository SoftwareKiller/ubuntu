#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string removeKdigits(string s, int k)
{
    if(k > s.size()) 
        return s;

    string result;
    for(size_t i = 0; i < s.size(); ++i) {
        while(!result.empty() && result.back() > s.at(i) && k) {
            --k;
            result.pop_back();
        }
        if(result.empty() && s.at(i) == '0')
            continue;
        result.push_back(s.at(i));
    }
    while(k && !result.empty()) {
        --k;
        result.pop_back();
    }
    return result == "" ? "0" : result;
}

int main() {
    string s{"1293834723"};
    cout << removeKdigits(s, 5) << endl;
    s = "10";
    cout << removeKdigits(s, 2) << endl;
}

