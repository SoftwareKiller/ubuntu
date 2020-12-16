#include<iostream>
#include<string>
using namespace std;
class test{
public:
    void Print(int i)
    {
        cout<<i<<endl;
    }

    void Print(string str)
    {
        cout<<str<<endl;
    }

    void Print(char c)
    {
        cout<<c<<endl;
    }
};

int main()
{
    test t;
    t.Print(10);
    t.Print("hello overload");
    t.Print('C');
    return 0;
}
