#include<iostream>
#include<stdlib.h>
using namespace std;

struct A
{
    int a[100000];
};

void Test(const A&a)
{}

void TestRef()
{
    A a;
    for(int i = 0; i < 1000000; i++)
        Test(a);
}

int main()
{
    int a = 10;
    int b = 20;
    int &ra = a;
    cout<<"a:"<<a<<" "<<&a<<" "<<"ra："<<ra<<" "<<&ra<<" "<<"b:"<<b<<" "<<&b<<endl;
    ra = b;
    cout<<"a:"<<a<<" "<<&a<<" "<<"ra："<<ra<<" "<<&ra<<" "<<"b:"<<b<<" "<<&b<<endl;
    TestRef();
    return 0;
}
