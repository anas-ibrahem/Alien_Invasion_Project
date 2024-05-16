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
    
    //Flags
    bool isInfected();
    bool isImmuned();
    //Setters
    void setInfected(bool Infect);
    void setImmuned(bool Immune);

    //Getters
    static int getInfected_Count() ;
    static int get_Total_Infected_Count();

    //Control Infection
    static void ReduceInfectedCount();
    static void IncreaseInfectedCount();

};

