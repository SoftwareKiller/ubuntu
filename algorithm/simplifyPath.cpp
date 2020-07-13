#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(const string& s, char delimiter)
{
    vector<string> ret;
    istringstream tokens(s);
    string output;
    while(getline(tokens, output, delimiter))
    {
        if(output == "" || output == "." || (output == ".." && ret.size() == 0))
            continue;
        else if(output == ".." && ret.size() > 0)
            ret.pop_back();
        else
            ret.push_back(output);
    }

    return ret;
}

string simplifyPath(string path)
{
    vector<string> field = split(path, '/');

    string ret;
    for(auto&i : field)
        ret = ret + "/" + i;

    return ret == "" ? "/" : ret;
}

int main()
{
    cout << simplifyPath("/home/") << endl;
    cout << simplifyPath("/../") << endl;
    cout << simplifyPath("/home//foo/") << endl;
    cout << simplifyPath("/a//b////c/d//././/..") << endl;
}

