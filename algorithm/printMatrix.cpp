#include <iostream>
#include <vector>

using namespace std;

void push(vector<int>& v, vector<vector<int> >& m, int left, int right, int low, int high);

vector<int> printMatrix(vector<vector<int> > matrix) {
    if(matrix.empty()) return {};
    vector<int> ret;
    int left = 0, right = matrix[0].size() - 1;
    int low = 0, high = matrix.size() - 1;
    while(left <= right && low <= high)
    {
        push(ret, matrix, left++, right--, low++, high--);
    }
    return ret;
}

void push(vector<int>& v, vector<vector<int> >& m, int left, int right, int low, int high)
{
    for(int i = left; i <= right; ++i)
    {
        v.push_back(m[low][i]);
    }

    if(low < high)
    {
        for(int i = low + 1; i <= high; ++i)
        {
            v.push_back(m[i][right]);
        }
    }
    if(left < right && low < high)
    {
        for(int i = right - 1; i >= left; --i)
        {
            v.push_back(m[high][i]);
        }
    }
    if(low + 1 < high && left < right)
    {
        for(int i = high - 1; i >= low + 1; --i)
        {
            v.push_back(m[i][left]);
        }
    }

}

int main()
{
    vector<vector<int>> v{ {1,2,3},
        {4,5,6},
        {7,8,9}};
    vector<int> ret = printMatrix(v);
    for(auto it : ret)
    {
        cout << it << " ";
    }
    cout << endl;

    vector<vector<int>> vv{ {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15}};

    auto r = printMatrix(vv);
    for(auto it : r)
    {
        cout << it << " ";
    }

    cout << endl;
}

