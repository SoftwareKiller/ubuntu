#include<iostream>
#include<ctime>

using namespace std;

void Fun()
{
    int data = 0;
    for(int i = 0; i < 10000000; i++)
    {
        data++;
    }
}

int main()
{
    int start = 0;
    int end = 0;
    int times = 0;
    start = clock();
    Fun();
    end = clock();

    times = (end - start)/CLOCKS_PER_SEC;

    cout<<end - start << endl;
    cout<< CLOCKS_PER_SEC << endl;
    cout<< times << endl;
    return 0;
}

