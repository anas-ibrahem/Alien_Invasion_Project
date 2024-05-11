#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"
#include "..\..\Game\Game.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower,game)
{


}



bool aSoldier::attack(LinkedQueue<unit*>& AttackedUnits)
{
	LinkedQueue<unit*>EStempList;
	LinkedQueue<unit*>StempList;
	int cap = AttackCapacity;


	while (cap > 0) {

		unit* tempES = nullptr;

		unit* tempS = nullptr;

		tempES = game->PickUnit(unit::ES);



		if (tempES) {
			if (tempES->getAttacked(this)) {

				game->AddToKilled(tempES); // If Unit Died MOVE IT TO KILLED LIST
			}
			else if (!game->AddUML(tempES)) 
			{
				EStempList.enqueue(tempES); // Else Move it to templist
			}
			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempES); // ADD ID to Print List
			cap--;
		}



		if (cap > 0)//check if capacity can offer another one 
			tempS = game->PickUnit(unit::SU);

		if (tempS)
		{
			 if (tempS->getAttacked(this))
				game->AddToKilled(tempS);
			 // If Unit Died MOVE IT TO KILLED LIST

			else 
				 StempList.enqueue(tempS); // Else Move it to templist

			if (game->getMode() == 'a')

				AttackedUnits.enqueue(tempS); // ADD ID to Print List

			cap--;
		}


		if (!tempES && !tempS)
			break;
		//nothing to Attack // Break the Loop

	}

	while (!EStempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		EStempList.dequeue(temp);
		game->AddUnit(temp);
	}
	while (!StempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		StempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
