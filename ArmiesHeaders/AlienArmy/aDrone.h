#pragma once
#include "..\unit.h"

class aDrone :public unit
{

	static int LastDroneID ;


public :

	aDrone(int Tj, int Health, int AttackCapacity, int AttackPower);
	aDrone();
	bool attack();
	int GetId();


};

