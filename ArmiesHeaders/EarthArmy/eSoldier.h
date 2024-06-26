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
    bool attack(LinkedQueue<unit*>& AttackedUnits);
    
    //Flags
    bool isInfected();
    bool isImmuned();
    //Setters
    void setInfected(bool Infect);
    void setImmuned(bool Immune);



};

