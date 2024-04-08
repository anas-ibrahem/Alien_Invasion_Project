#pragma once
#include "..\unit.h"
template<class T>
class LinkedQueue;

class eSoldier :
    public unit
{
    
public:

    eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
    virtual bool attack();

};

