#include "..\..\ArmiesHeaders\AlliedArmy\alSaver.h"
#include "..\..\Game\Game.h"


alSaver::alSaver(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , SU, Tj, Health, AttackCapacity, AttackPower,game)
{
}

bool alSaver::attack(LinkedQueue<unit*>& AttackedUnits) {

	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;

	while (cap > 0) {

		unit* temp=nullptr;

		temp = game->PickUnit(unit::AS);

		

		if (temp) {
			if (temp->getAttacked(this)) {

				game->AddToKilled(temp); // If Unit Died MOVE IT TO KILLED LIST
			}
			else {
				tempList.enqueue(temp); // Else Move it to templist
			}

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(temp); // ADD ID to Print List
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