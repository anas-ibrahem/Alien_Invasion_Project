#pragma once
#include "../Army.h"
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"
#include "eHeal.h"


class EarthArmy : public Army {
private:
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*>Gunneries ;
	ArrayStack<unit*> Healers;
	priQueue<unit*> UML;

public:
	EarthArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();
	unit* PickUnit(unit::UnitType type , char dronedir = 'f');
	bool AddtoUML(unit* unit);
	void attack();
	~EarthArmy();

};