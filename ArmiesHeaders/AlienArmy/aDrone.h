#include "..\unit.h"

class aDrone :public unit
{

	static int LastDroneID ;


public :
	aDrone( int Tj, int Ta, int Health, int AttackCapacity);
	aDrone();
	bool attack();
	bool defend();
	int GetId();


};

