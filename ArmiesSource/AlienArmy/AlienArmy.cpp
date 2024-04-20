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



