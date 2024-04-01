#include "..\..\ArmiesHeaders\AlienArmy\AlienArmy.h"

AlienArmy::AlienArmy() {

	DronesCount = 0;


}

bool AlienArmy::AddUnit(unit* unit)
{

	switch (unit->GetType()) {
	
	case AD: {
		return Drones.enqueue(unit);
	}
	case AS :
	{
		return Soldiers.enqueue(unit);
	}
	case AM: {
		Monsters[MonsterCount++] = unit;
		break;
	}
	
	
	}
}
