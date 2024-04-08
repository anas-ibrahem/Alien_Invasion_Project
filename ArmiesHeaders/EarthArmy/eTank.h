#pragma once
#include "..\unit.h"


class eTank :
    public unit
{
 
public:
    eTank(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    virtual bool attack();
};

