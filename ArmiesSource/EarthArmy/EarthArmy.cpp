#include "..\..\ArmiesHeaders\EarthArmy\EarthArmy.h"

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
	default:
		return false;
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

unit* EarthArmy::PickUnit(unit::UnitType type , char dronedir)
{
	unit* temp = nullptr ;
	int I; // Dummy integer

	switch (type) {
	case unit::ET : 
			 Tanks.pop(temp);
			 break;
	case unit::ES:
			 Soldiers.dequeue(temp);
			 break;
	case unit::EG:
			 Gunneries.dequeue(temp , I);
			 break;

	default:
		break;
		 
	}


	return temp;
}

void EarthArmy::attack()
{
	// Check IF null
	unit* Attacker = nullptr;

	
	if (Soldiers.peek(Attacker)) Attacker->attack();

	//Tanks.peek()->attack();
	//Gunneries.peek()->attack();



}

void EarthArmy::PrintAttack()
{
}



EarthArmy::~EarthArmy()
{
}