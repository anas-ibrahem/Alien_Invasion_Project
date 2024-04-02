#pragma once
#include "..\unit.h"

class aMonster :public unit
{

	static int LastMonsterID;


public:
	aMonster(int Tj, int Health, int AttackCapacity, int AttackPower);
	aMonster();
	bool attack();
	int GetId();


};

