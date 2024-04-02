#pragma once
#include "..\unit.h"


class eGunnery :
    public unit
{
    static int LastGunneryID;
public:

    eGunnery(int Tj, int Health, int AttackCapacity, int AttackPower);
    eGunnery();
    virtual bool attack();
};

