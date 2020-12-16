#include <iostream>
#include "calculate.h"
#include "subclass.h"

using namespace std;

class ProcessData
{
public:

    ProcessData(int x, int y):
        x_(x),
        y_(y)
    {
    }

    int peocess(Calculate* handle)
    {
        return  handle->calculate(x_, y_);
    }
private:
    int x_;
    int y_;
};

int main()
{
    int x = 10;
    int y = 10;
    Add add;
    ProcessData pd(x, y);
    int ret = pd.peocess(&add);
    cout << "Add " <<ret << endl;
    Sub sub;
    ret = pd.peocess(&sub);
    cout << "Sub " <<ret << endl;
    return 0;
}

