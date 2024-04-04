#include "..\..\ArmiesHeaders\EarthArmy\EarthArmy.h"

bool EarthArmy::AddUnit(unit* unit)
{
	switch (unit->GetType()) {
	case ET:
		return Tanks.push(unit);
	case ES:
		return Soldiers.enqueue(unit);
	case EG:
		return Gunneries.enqueue(unit,unit->getPower()*unit->getHealth());
	}
}


