/*
 * 给定一个字符串，找出其中不含重复字符的“最长字串”
 * */

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

/*int lengthOfLongestSubstring(string s)
{
    if(s.length() <= 1)
        return s.length();
    string::size_type pos = string::npos;
    string::size_type last_pos = 0;
    int i = 0;
    char start = s[i];
    int max = 0;
    if(i < s.length() - 1)
        last_pos = s.find_first_of(start, ++i);
    while(last_pos == string::npos && i <= s.length() - 1)
    {
        ++max;
        start = s[++i];
        last_pos = s.find_first_of(start, i);
    }
    if((last_pos - pos) > max)
        max = last_pos - pos;
    while( (max < (s.length() - last_pos)) && last_pos != string::npos)
    {
        if(i >= s.length() - 1)
            return max;
        pos = last_pos;
        start = s[++i];
        last_pos = s.find_first_of(start, pos + 1);
        if(last_pos == string::npos)
        {
            if((s.length() - pos) > max)
                max = s.length() - pos;
        }
        else if((last_pos - pos) > max)
            max = last_pos - pos;
    }
    return max;
}*/

int lengthOfLongestSubstring(string s)
{
    unordered_set<char> unique_s;

    int right_pos = -1, ret = 0;

    int size = s.size();

    for(int i = 0; i < size; ++i)
    {
        if(i != 0)
        {
            //每个循环向前推进一位，从第二次循环开始
            unique_s.erase(s[i-1]);
        }

        //unique_s.count会一直向前探寻重复字符，如果重复，结束本次循环
        while(right_pos + 1 < size && !unique_s.count(s[right_pos + 1]))
        {
            unique_s.insert(s[right_pos + 1]);
            ++right_pos;
        }

        //求出从i到right_pos的长度和当前最长的长度
        ret = max(ret, right_pos - i + 1);
    }

    return ret;
}

int main()
{
    string s{"abcabcbb"};
    cout << lengthOfLongestSubstring(s) << endl;
    s = "bbbbbb";
    cout << lengthOfLongestSubstring(s) << endl;
    s = "pwwkew";
    cout << lengthOfLongestSubstring(s) << endl;
}

