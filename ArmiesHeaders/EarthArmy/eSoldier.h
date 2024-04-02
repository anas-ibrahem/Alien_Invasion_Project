#pragma once
#include "..\unit.h"


class eSolider :
    public unit
{
    static int LasteSoliderID;
public:
    eSolider();
    eSolider(int Tj, int Health, int AttackCapacity, int AttackPower);
    virtual bool attack();
};

