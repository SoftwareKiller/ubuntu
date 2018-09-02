#include <iostream>
using namespace std;

void quickSort(int arr[], int left, int right)
{
    int key = arr[left];
    int i=left, j=right;
    if(i>j)
        return;
    while(i<j)
    {
        while(i<j && arr[j] >= key)
            j--;
        arr[i] = arr[j];
        while(i<j && arr[i] <= key)
            i++;
        arr[j] = arr[i];
    }
    arr[i] = key;
    quickSort(arr, left, i-1);
    quickSort(arr, i+1, right);
}

int main()
{
    int arr[] = {3, 9, 8, 2, 4, 6, 10, 19, 21, 23, 13, 89, 57, 52, 32};
    int len = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, len-1);
    for(int i=0; i<len; ++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
