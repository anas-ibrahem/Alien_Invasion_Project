#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"
#include "..\..\Game\Game.h"


eSoldier::eSoldier(int id, int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id, ES, Tj, Health, AttackCapacity, AttackPower, game)
{
	infected = false;
	immuned = false;
}


bool eSoldier::attack(LinkedQueue<unit*>& AttackedUnits)
{
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	unit* Attacker = nullptr; // Used in Case of Infection no need for it in No infected

	if (infected)
	{
		Attacker = game->PickUnit(unit::ES); //Hold the infected Attacker ES
	}

	while (cap > 0) {

		unit* temp = nullptr;
		if (!infected)
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

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(temp); // ADD unit to Print List
			cap--;
		}

		if (!temp)
			break;
		//nothing to Attack // Break the Loop

	}
	

	if (infected) 
	{
		unit* temp = nullptr;
		// we will need to empty the the whole ES list in the temp list to keep the order of the queue in this case
		while (temp = game->PickUnit(unit::ES))
			tempList.enqueue(temp);

		game->AddUnit(Attacker); // return the Attacker As the First Of the List
	}

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