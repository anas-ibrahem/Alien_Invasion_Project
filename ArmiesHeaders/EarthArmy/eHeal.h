#pragma once
#include "..\unit.h"


class eHeal :
    public unit
{
    
public:

    eHeal(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    virtual bool attack();
};

