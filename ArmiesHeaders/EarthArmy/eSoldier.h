#pragma once
#include "..\unit.h"


class Game;

class eSoldier :
    public unit
{
private:
    bool infected;
    bool immuned;
    static int Infected_Count;
    static int Infected_Count_Total;

public:

    eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    bool attack(LinkedQueue<unit*>& AttackedUnits);
    bool isInfected();
    bool isImmuned();
    void setInfected(bool Infect);
    void setImmuned(bool Immune);
    static int getInfected_Count() ;
    static int get_Total_Infected_Count();
    static void ReduceInfectedCount();

};

