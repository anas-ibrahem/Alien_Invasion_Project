#pragma once
#include "../Army.h"
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"


class EarthArmy : public Army {
private:
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*>Gunneries ;

public:
	EarthArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();


	LinkedQueue<unit*>& GetSoldiers();
	~EarthArmy();

};