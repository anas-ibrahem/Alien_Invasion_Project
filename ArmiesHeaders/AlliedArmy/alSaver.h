#pragma once
#include "..\unit.h"


class Game;

class alSaver :
    public unit
{
    
public:

    alSaver(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<int>& AttackedIDs);

};

