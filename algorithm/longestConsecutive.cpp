#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int longestConsecutive_(const vector<int>& v) {
    unordered_map<int, bool> hash;
    for(auto& i : v)
        hash[i] = false;

    int longest = 0;
    for(auto& i : v) {
        if(hash[i])
            continue;

        hash[i] = true;
        int length = 1;
        for(int j = i + 1; hash.find(j) != hash.end(); ++j) {
            hash[j] = true;
            ++length;
        }

        for(int j = i - 1; hash.find(j) != hash.end(); --j) {
            hash[j] = true;
            ++length;
        }

        longest = max(longest, length);
    }

    return longest;
}

int mergeCluster(unordered_map<int, int>& map, int left ,int right);

int longestConsecutive(const vector<int>& v) {
    unordered_map<int, int> map;
    size_t size = v.size();
    int l = 1;
    for(size_t i = 0; i < size; ++i) {
        if(map.find(v[i]) != map.end())
            continue;

        map[v[i]] = 1;
        if(map.find(v[i] - 1) != map.end()) {
            l = max(l, mergeCluster(map, v[i] - 1, v[i]));
        }
        if(map.find(v[i] + 1) != map.end()) {
            l = max(l, mergeCluster(map, v[i], v[i] + 1));
        }
    }

    return size == 0 ? 0 : l;
}

//记录并更新边界长度
int mergeCluster(unordered_map<int, int>& hash, int left ,int right) {
    int upper = right + hash[right] - 1;
    int lower = left - hash[left] + 1;
    int length = upper - lower + 1;
    hash[upper] = length;
    hash[lower] = length;
    return length;
}

int main() {
    vector<int> v{1,9,2,3,7,8,11,10};
    cout << longestConsecutive(v) << endl;
}

