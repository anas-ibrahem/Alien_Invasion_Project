#pragma once
#include "..\unit.h"

class aDrone :public unit
{



public :

	aDrone(int id ,int Tj, int Health, int AttackCapacity, int AttackPower);
	aDrone();
	bool attack();
	int GetId();


};

