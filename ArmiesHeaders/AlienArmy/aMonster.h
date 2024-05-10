#pragma once
#include "..\unit.h"

class aMonster :public unit
{
	static int AM_Infect_Prob;


public:

	aMonster(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
	bool attack(LinkedQueue<unit*>& AttackedUnits);
	static void set_AM_Infect_Prob(int prob);
	bool WillInfect() const;

};

