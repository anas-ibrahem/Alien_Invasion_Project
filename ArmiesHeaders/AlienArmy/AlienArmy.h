#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../Army.h"
#include "..\..\DS\DoubleLinkedQueue.h"
#include "..\..\DS\LinkedQueue.h"
#include "..\..\DS\DynamicArray.h"


class AlienArmy : public Army {
private:
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	DynamicArray<unit*> Monster;

public :
	AlienArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();

	LinkedQueue<unit*> &GetSoldiers();
	DynamicArray<unit*>& GetMonsters();


};