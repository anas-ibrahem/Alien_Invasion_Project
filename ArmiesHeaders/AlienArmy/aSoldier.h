#pragma once
#include "..\unit.h"


class aSolider :
    public unit
{
public:
    virtual bool attack();
    virtual bool defend();
    virtual bool isDead();
};

