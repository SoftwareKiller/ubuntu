#include "subclass.h"

int Add::calculate(int x, int y)
{
    return x + y;
}

Add::~Add()
{
}

int Sub::calculate(int x, int y)
{
    return x - y;
}

Sub::~Sub()
{
}
