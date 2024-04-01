#pragma once
#include "..\unit.h"

class aDrone :public unit
{

	static int LastDroneID ;


public :
	aDrone( int Tj, int Health, int AttackCapacity);
	aDrone();
	bool attack();
	bool defend();
	int GetId();


};

