#include "..\..\ArmiesHeaders\AlienArmy\AlienArmy.h"

AlienArmy::AlienArmy() {
	LastAddedAD = 'r';
}

bool AlienArmy::AddUnit(unit* unit)
{

	switch (unit->GetType()) {
	
		

	case unit::AD: {
		
		if (LastAddedAD == 'r')
		{
			LastAddedAD = 'f';
			return Drones.enqueue_front(unit);
		}
		else if (LastAddedAD == 'f')
		{
			LastAddedAD = 'r';
			return Drones.enqueue_rear(unit);
		}

	}
	case unit::AS :
	{
		return Soldiers.enqueue(unit);
	}
	case unit::AM: {
		return Monster.insert(unit);
	}
	
	default :
		return false;
	
	
	}
}

void AlienArmy::PrintAliveUnits()
{
	cout << "=============== Alien Army Alive Units ===============" << endl;
	cout << Soldiers.getCount() << " AS: ";
	Soldiers.print();
	cout << endl << endl << Drones.getCount() << " AD: ";
	Drones.print();
	cout << endl << endl << Monster.getCount() << " AM: ";
	Monster.print();
	cout << endl << endl;

}

bool AlienArmy::PrintFights()
{
	bool AS_Is_Attacked = !AS_Attacked.isEmpty();
	bool AM_Is_Attacked = !AM_Attacked.isEmpty();
	bool AD_Is_Attacked = !AD_Attacked.isEmpty();

	if (AS_Is_Attacked)
		PrintFight(unit::AS);

	if (AM_Is_Attacked)
		PrintFight(unit::AM);

	if (AD_Is_Attacked)
		PrintFight(unit::AD);


	return (AS_Is_Attacked || AM_Is_Attacked || AD_Is_Attacked );
}


void AlienArmy::PrintFight(unit::UnitType type) {

	int id;

	switch (type) {

	case unit::AS:
		cout << "AS " << AS_AttackerID << " Attacked [ ";

		while (AS_Attacked.dequeue(id))
		{
			cout << id;
			if (!AS_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;

	case unit::AM:
		cout << "AM " << AM_AttackerID << " Attacked [ ";

		while (AM_Attacked.dequeue(id))
		{
			cout << id;
			if (!AM_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;


	case unit::AD:
		cout << "AD " << AD_AttackerID_Front << " & " << AD_AttackerID_Rear << " Attacked [ ";

		while (AD_Attacked.dequeue(id))
		{
			cout << id;
			if (!AD_Attacked.isEmpty()) cout << " , ";
			else cout << " ]\n";
		}
		break;

	default:
		break;
	}

	return;

}


unit* AlienArmy::PickUnit(unit::UnitType type , char dronedir )
{
	
		unit* temp = nullptr ;

		switch (type) {
		case unit::AS:
			Soldiers.dequeue(temp);
			break;
		case unit::AM:

			temp = Monster.PickRand();
			break;

		case unit::AD :


			if (dronedir == 'f') // Front dequeue
				Drones.dequeue_front(temp);
			else if (dronedir == 'r') // Rear Dequeue
				Drones.dequeue_rear(temp);

			break;

		default:
			break;

		}
		return temp;
}

void AlienArmy::attack()
{
	unit* Attacker = nullptr;

	if (Soldiers.peek(Attacker))
	{
		Attacker->attack(AS_Attacked);
		AS_AttackerID = Attacker->getID();
	}

	if (Monster.PeekRand(Attacker))
	{
		Attacker->attack(AM_Attacked);
		AM_AttackerID = Attacker->getID();
	}



}

AlienArmy::~AlienArmy()
{
}
