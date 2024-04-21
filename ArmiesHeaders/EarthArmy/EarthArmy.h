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
	unit* PickUnit(unit::UnitType type , char dronedir = 'f');
	void attack();
	void PrintAttack();
	~EarthArmy();

};