#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int findRepeatNumber(vector<int>& v) {
    unordered_map<int,int> hash;
    for(size_t i = 0; i < v.size(); ++i) {
        if(hash.find(v[i]) != hash.end())
            return v[i];
        else
            hash[v[i]] = 1;
    }

    return -1;
}

int main() {
    vector<int> v{2, 3, 1, 0, 2, 5, 3};
    cout << findRepeatNumber(v) << endl;
}

