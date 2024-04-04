#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "..\..\DS\DoubleLinkedQueue.h"
#include "..\..\DS\LinkedQueue.h"
#include "..\..\DS\DynamicArray.h"


class AlienArmy {
private:
	int DronesCount;
	int MonsterCount;
	int SoldierCount;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	DynamicArray<unit*> Monster;

public :
	AlienArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();


};