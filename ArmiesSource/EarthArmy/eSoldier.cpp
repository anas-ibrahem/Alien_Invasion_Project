#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"
#include "..\..\Game\Game.h"


int eSoldier::Infected_Count = 0;


eSoldier::eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , ES, Tj, Health, AttackCapacity, AttackPower,game)
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

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(temp); // ADD ID to Print List
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
	if (Infect) Infected_Count++;
	else Infected_Count--;

}

void eSoldier::setImmuned(bool Immune)
{
	immuned = Immune;
}

int eSoldier::getInfected_Count()
{
	return Infected_Count;
}

int eSoldier::ReduceInfectedCount()
{
	return Infected_Count--;
}