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
	case unit::EH:
		return Healers.push(unit);
	default:
		return false;
	}
}





void EarthArmy::PrintAliveUnits()
{
	cout << "=============== Earth Army Alive Units ===============" << endl;
	cout << Soldiers.getCount() << " ES: ";
	Soldiers.print();
	cout << endl << endl << Tanks.getCount() << " ET: ";
	Tanks.print();
	cout << endl << endl << Gunneries.getCount() << " EG: ";
	Gunneries.print();
	cout << endl << endl << Healers.getCount() << " EH: ";
	Healers.print();
	cout << endl << endl << "=============== Unit Maintenance Units ===============" << endl;
	cout << UML.getCount() << " UML: ";
	UML.print();
}

void EarthArmy::PrintFights()
{
	
		int id;
		ET_Crnt_attack.dequeue(id); // Always Dequeue The Attacker

		if (!ET_Crnt_attack.isEmpty())
		{
			cout << "ET  " << id << " shots [ ";
			PrintAttacked(unit:: ET);

		}
}

void EarthArmy::PrintAttacked(unit::UnitType type) {
	int id;

	switch (type)
	{
	case unit::ES:
		break;
	case unit::ET:

		while (ET_Crnt_attack.dequeue(id))
		{
			cout << id;
		if (!ET_Crnt_attack.isEmpty())
			cout << " , ";
		}
		cout << " ]" << endl;

		break;
	case unit::EG:
		break;
	case unit::EH:
		break;
	default:
		break;
	}




}

unit* EarthArmy::PickUnit(unit::UnitType type , char dronedir)
{
	unit* temp = nullptr ;
	int I; // Dummy integer

	switch (type) {
	case unit::ET:
		Tanks.pop(temp);
		break;
	case unit::ES:
		Soldiers.dequeue(temp);
		break;
	case unit::EG:
		Gunneries.dequeue(temp, I);
		break;
	case unit::EH:
		Healers.pop(temp);
		break;
	default:
		break;

	}


	return temp;
}

bool EarthArmy::AddtoUML(unit* unit)
{
	if (unit)
		switch (unit->GetType())
		{
		case unit::ES:
			if(UML.enqueue(unit, INT_MAX / unit->getHealth()))
				return true;
			break;
		case unit::ET:
			if(UML.enqueue(unit, -1))
				return true;
			break;
		default:
			break;
		}
	return false;
}

void EarthArmy::attack()
{
	unit* Attacker = nullptr;

	//if (Soldiers.peek(Attacker))
	//	Attacker->attack( );

	if (Tanks.peek(Attacker))
		Attacker->attack(ET_Crnt_attack);


}


EarthArmy::~EarthArmy()
{
}