#pragma once
#include "..\unit.h"


class eTank :
    public unit
{
    static int LastTankID;
public:
    eTank();
    eTank(int Tj, int Health, int AttackCapacity, int AttackPower);
    virtual bool attack();
};

