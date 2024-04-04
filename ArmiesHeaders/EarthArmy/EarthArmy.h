#pragma once
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"
#include "..\..\DS\priQueue.h"
#include "..\..\DS\LinkedQueue.h"
#include "..\..\DS\ArrayStack.h"

class EarthArmy {
public:
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*> Gunneries;

private:
	EarthArmy();
	bool AddUnit(unit* unit);


};