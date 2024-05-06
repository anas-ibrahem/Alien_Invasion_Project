#pragma once
#include "..\unit.h"


class eGunnery :
    public unit
{
    
public:

    eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<int>& AttackedIDs, LinkedQueue<int>& InfectedIDS);
};

