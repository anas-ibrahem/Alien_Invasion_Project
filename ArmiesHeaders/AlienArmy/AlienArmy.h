#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/LinkedQueue.h"


class AlienArmy {
private:
	int DronesCount;
	DoubleLinkedQueue <unit*> Drones;
	LinkedQueue <unit*> Soldiers;


public :
	AlienArmy();
	bool AddUnit(unit* unit);


};