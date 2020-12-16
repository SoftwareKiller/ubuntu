#pragma once
#include "calculate.h"

class Add : public Calculate
{
public:
    virtual int calculate(int x, int y) override;

    virtual ~Add();
};

class Sub : public Calculate
{
public:
    virtual int calculate(int x, int y) override;

    virtual ~Sub();
};
