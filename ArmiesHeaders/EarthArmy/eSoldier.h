#pragma once
#include "..\unit.h"


class Game;

class eSoldier :
    public unit
{
    
public:

    eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<int>& AttackedIDs);

};

