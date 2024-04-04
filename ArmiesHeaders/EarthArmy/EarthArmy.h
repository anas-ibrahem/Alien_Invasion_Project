#pragma once
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"
#include "..\..\DS\priQueue.h"
#include "..\..\DS\LinkedQueue.h"
#include "..\..\DS\ArrayStack.h"

class EarthArmy {
private:
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*>Gunneries ;

public:
	EarthArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();

};