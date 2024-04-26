#include "..\..\ArmiesHeaders\EarthArmy\EarthArmy.h"

EarthArmy::EarthArmy(){}


bool EarthArmy::AddUnit(unit* unit, char InsertDir)
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

bool EarthArmy::PrintFights()
{
	bool ES_Is_Attacked = !ES_Attacked.isEmpty();
	bool ET_Is_Attacked = !ET_Attacked.isEmpty();
	bool EG_Is_Attacked = !EG_Attacked.isEmpty();
	bool EH_Is_Attacked = !EH_Attacked.isEmpty();

	if (EH_Is_Attacked)
		PrintFight(unit::EH);

	if (ES_Is_Attacked)
		PrintFight(unit::ES);

	if (ET_Is_Attacked)
		PrintFight(unit::ET);

	if (EG_Is_Attacked)
		PrintFight(unit::EG);



	return (ES_Is_Attacked || ET_Is_Attacked || EG_Is_Attacked || EH_Is_Attacked );
}

void EarthArmy::PrintFight(unit::UnitType type) {

	int id;

	switch (type) {
	
	case unit::ES :
		cout << "ES " << ES_AttackerID << " Attacked [ ";
		
		while (ES_Attacked.dequeue(id))
		{
			cout << id;
			if (!ES_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;

	case unit::ET:
		cout << "ET " << ET_AttackerID << " Attacked [ ";

		while (ET_Attacked.dequeue(id))
		{
			cout << id;
			if (!ET_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;


	case unit::EG:
		cout << "EG " << EG_AttackerID << " Attacked [ ";

		while (EG_Attacked.dequeue(id))
		{
			cout << id;
			if (!EG_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;

	case unit::EH:
		cout << "EH " << EH_AttackerID << " Healed [ ";

		while (EH_Attacked.dequeue(id))
		{
			cout << id;
			if (!EH_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
	
	
	default :
		break;
	}

	return;

}

unit* EarthArmy::PickUnit(unit::UnitType type , char PickDir)
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

unit* EarthArmy::PickfromUML()
{
	unit* temp = nullptr;
	int I; // Dummy integer
	UML.dequeue(temp, I);
	return temp;
}

void EarthArmy::attack()
{
	unit* Attacker = nullptr;

	if (Healers.pop(Attacker))
	{
		Attacker->attack(EH_Attacked);
		EH_AttackerID = Attacker->getID();
	}

	if (Soldiers.peek(Attacker))
	{
		Attacker->attack(ES_Attacked);
		ES_AttackerID = Attacker->getID();
	}

	if (Tanks.peek(Attacker))
	{
		Attacker->attack(ET_Attacked);
		ET_AttackerID = Attacker->getID();
	}

	int I; // Dummy Int 
	if (Gunneries.peek(Attacker , I))
	{
		Attacker->attack(EG_Attacked);
		EG_AttackerID = Attacker->getID();
	}


}


EarthArmy::~EarthArmy()
{
}