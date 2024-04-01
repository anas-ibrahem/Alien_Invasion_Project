#pragma once
#include "..\unit.h"

class aMonster :public unit
{

	static int LastMonsterID;


public:
	aMonster(int Tj, int Health, int AttackCapacity);
	aMonster();
	bool attack();
	bool defend();
	int GetId();


};

