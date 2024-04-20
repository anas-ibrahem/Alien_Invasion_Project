#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../Army.h"



class AlienArmy : public Army {
private:
	char LastAddedAD;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	DynamicArray<unit*> Monster;

public :
	AlienArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();
	unit* PickUnit(unit::UnitType type , char dronedir = 'f');



};