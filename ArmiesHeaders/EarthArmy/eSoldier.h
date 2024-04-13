#pragma once
#include "..\unit.h"


class eSoldier :
    public unit
{
    
public:

    eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    virtual bool attack();

};

