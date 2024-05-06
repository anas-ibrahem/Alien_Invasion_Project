#pragma once
#include "..\unit.h"


class Game;

class eSoldier :
    public unit
{
private:
    bool infected;
    bool immuned;
    
public:

    eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<int>& AttackedIDs, LinkedQueue<int>& InfectedIDS);
    bool isInfected();
    bool isImmuned();
    void setInfected(bool Infect);
    void setImmuned(bool Immune);


};

