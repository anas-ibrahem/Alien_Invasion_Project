#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"
#include "..\..\Game\Game.h"


eSoldier::eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , ES, Tj, Health, AttackCapacity, AttackPower,game)
{
	infected = false;
	immuned = false;
}


bool eSoldier::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	unit* Attacker = nullptr; // Used in Case of Infection no need for it in No infected

	if (infected)
		Attacker = game->PickUnit(unit::ES);

	while (cap > 0) {

		unit* temp = nullptr;
		if(!infected)
			temp = game->PickUnit(unit::AS);
		else
			temp = game->PickUnit(unit::ES);

		if (temp) {
			if (temp->getAttacked(this)) {

				game->AddToKilled(temp); // If Unit Died MOVE IT TO KILLED LIST
			}
			else {
				tempList.enqueue(temp); // Else Move it to templist
			}

			AttackedIDs.enqueue(temp->getID()); // ADD ID to Print List
			cap--;
		}

		if (!temp)
			break;
		//nothing to Attack // Break the Loop

	}

	if (Attacker) // Return Attacker In First (Assumption)
		game->AddUnit(Attacker);

	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}



	return (cap < AttackCapacity);

}

bool eSoldier::isImmuned()
{
	return immuned;
}

bool eSoldier::isInfected()
{
	return infected;
}

void eSoldier::setInfected(bool Infect)
{
	infected = Infect;
}

void eSoldier::setImmuned(bool Immune)
{
	immuned = Immune;
}
