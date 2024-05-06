#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"
#include "..\..\Game\Game.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower,game)
{


}



bool aSoldier::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;

	while (cap > 0) {

		unit* temp = nullptr;

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

	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
