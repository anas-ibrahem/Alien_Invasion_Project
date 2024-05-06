#pragma once
#include "..\unit.h"


class eTank :
    public unit
{
 
private:
    static bool AttackSoldiers;

public:
    eTank(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<int>& AttackedIDs, LinkedQueue<int>& InfectedIDS);

};

