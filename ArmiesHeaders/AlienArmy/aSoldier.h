#pragma once
#include "..\unit.h"


class aSoldier :
    public unit
{

public:


    aSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<unit*>& AttackedUnits);
};

