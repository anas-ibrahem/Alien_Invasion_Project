#pragma once
#include "..\unit.h"


class ES :
    public unit
{
public:
    virtual bool attack();
    virtual bool defend();
    virtual bool isDead();
};

