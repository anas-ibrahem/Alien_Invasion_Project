#include "aDrone.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/LinkedQueue.h"


class AlienArmy {

	int DronesCount;
	DoubleLinkedQueue <unit*> Drones;
	LinkedQueue <unit*> Soldiers;


private :
	AlienArmy();
	bool AddUnit(unit* unit);


};