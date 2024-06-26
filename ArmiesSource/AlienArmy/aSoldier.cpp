#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"
#include "..\..\Game\Game.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower,game)
{


}



bool aSoldier::attack(LinkedQueue<unit*>& AttackedUnits)
{
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;


	while (cap > 0) {

		unit* tempES = nullptr;

		unit* tempSU = nullptr;

		tempES = game->PickUnit(unit::ES);



		if (tempES) 
		{
			if (tempES->getAttacked(this)) {

				game->AddToKilled(tempES); // If Unit Died MOVE IT TO KILLED LIST
			}
			else if (tempES->CanJoinUML())
			{
				game->AddtoUML(tempES);
			}
			else 
				tempList.enqueue(tempES);

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(tempES); // ADD unit to Print List

			cap--;
		}



		if (cap > 0)//check if capacity can offer another one 
			tempSU = game->PickUnit(unit::SU);

		if (tempSU)
		{
			 if (tempSU->getAttacked(this))
				game->AddToKilled(tempSU);// If Unit Died MOVE IT TO KILLED LIST
						 
			else 
				 tempList.enqueue(tempSU); // Else Move it to templist

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(tempSU); // ADD ID to Print List

			cap--;
		}


		if (!tempES && !tempSU)
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
