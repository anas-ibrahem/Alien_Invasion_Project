#pragma once
#include "..\unit.h"


class eTank :
    public unit
{
 
public:
    eTank();
    eTank(int id ,int Tj, int Health, int AttackCapacity, int AttackPower);
    virtual bool attack();
};

