#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/LinkedQueue.h"


class AlienArmy {
private:
	int DronesCount;
	int MonsterCount;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	unit** Monsters = new unit*[1000];

public :
	AlienArmy();
	bool AddUnit(unit* unit);


};