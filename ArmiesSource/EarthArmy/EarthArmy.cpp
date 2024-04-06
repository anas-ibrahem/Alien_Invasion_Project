#include "..\..\ArmiesHeaders\EarthArmy\EarthArmy.h"
#include"cmath"
EarthArmy::EarthArmy(){}

bool EarthArmy::AddUnit(unit* unit)
{
	switch (unit->GetType()) {
	case unit::ET:
		return Tanks.push(unit);
	case unit::ES:
		return Soldiers.enqueue(unit);
	case unit::EG:
		return Gunneries.enqueue(unit,unit->getPower()*unit->getHealth());
	}
}

void EarthArmy::PrintAliveUnits()
{
	cout << "=============== Earth Army Alive Units ===============" << endl;
	cout << Soldiers.getCount() << " ES: ";
	Soldiers.print();
	cout << endl << endl <<  Tanks.getCount() << " ET: ";
	Tanks.print();
	cout << endl << endl<<   Gunneries.getCount() << " EG: ";
	Gunneries.print();
	cout << endl << endl;
}


