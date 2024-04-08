#include "..\..\ArmiesHeaders\AlienArmy\AlienArmy.h"

AlienArmy::AlienArmy() {
}

bool AlienArmy::AddUnit(unit* unit)
{

	switch (unit->GetType()) {
	
		

	case unit::AD: {
		return Drones.enqueue(unit);
	}
	case unit::AS :
	{
		return Soldiers.enqueue(unit);
	}
	case unit::AM: {
		return Monster.insert(unit);
	}
	
	
	
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

LinkedQueue<unit*>& AlienArmy::GetSoldiers()
{
	return Soldiers;
}


