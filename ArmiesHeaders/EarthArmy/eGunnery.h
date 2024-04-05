#pragma once
#include "..\unit.h"


class eGunnery :
    public unit
{
    
public:

    eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower);
    eGunnery();
    virtual bool attack();
};

