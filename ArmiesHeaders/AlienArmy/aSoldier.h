#pragma once
#include "..\unit.h"


class aSolider :
    public unit
{
    static int LastSoliderID;
public:
    aSolider();
    aSolider(int Tj, int Health, int AttackCapacity, int AttackPower);
    virtual bool attack();
};

