#pragma once
#include "..\unit.h"


class eSolider :
    public unit
{
    
public:
    eSolider();
    eSolider(int Tj, int Health, int AttackCapacity, int AttackPower);
    virtual bool attack();
};

