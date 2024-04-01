#pragma once
#include "aDrone.h"
#include "aMonster.h"
#include "..\..\DS\DoubleLinkedQueue.h"
#include "..\..\DS\LinkedQueue.h"
#include "..\..\DS\ArrayStack.h"


class AlienArmy {

	int DronesCount;
	int MonsterCount;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	unit** Monsters = new unit*[1000];

private :
	AlienArmy();
	bool AddUnit(unit* unit);


};