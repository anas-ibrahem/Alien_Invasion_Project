#pragma once
#include "..\unit.h"

class aMonster :public unit
{



public:

	aMonster(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
	bool attack(LinkedQueue<int>& AttackedIDs);

};

