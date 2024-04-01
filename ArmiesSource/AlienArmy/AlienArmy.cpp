#include "..\..\ArmiesHeaders\AlienArmy\AlienArmy.h"

AlienArmy::AlienArmy() {

	DronesCount = 0;


}

bool AlienArmy::AddUnit(unit* unit)
{

	switch (unit->GetType()) {
	
	case AD: {
		Drones.enqueue(unit);
		break;
	}
	case AS :
	{
		Soldiers.enqueue(unit);
		break;
	}
	
	
	
	}
}
