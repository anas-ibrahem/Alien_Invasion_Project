#pragma once
#include "..\unit.h"


class eHeal :
    public unit
{
    
public:

    eHeal(int id ,int Tj, double Health, int AttackCapacity, double AttackPower, Game* game);
    bool attack(LinkedQueue<unit*>& AttackedUnits);
};

