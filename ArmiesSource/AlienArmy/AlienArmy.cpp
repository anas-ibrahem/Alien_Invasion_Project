#include "..\..\ArmiesHeaders\AlienArmy\AlienArmy.h"

AlienArmy::AlienArmy() {

	DronesCount = 0;
	MonsterCount = 0;

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
		return Monster.insert(unit);
	}
	
	
	
	}
}

void AlienArmy::PrintAliveUnits()
{
	cout << "=============== Alien Army Alive Units ===============" << endl;
	cout << Soldiers.getCount() << " AS: ";
	Soldiers.print();
	cout << endl << Drones.getCount() << " AD: ";
	Drones.print();
	cout << endl << Monster.getCount() << " AM: ";
	Monster.print();


}


