#include "..\..\ArmiesHeaders\AlienArmy\aDrone.h"
#include "..\..\Game\Game.h"

aDrone::aDrone(int id , int Tj , int Health , int AttackCapacity , int AttackPower, Game* game) :
	unit(id , AD , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}



bool aDrone::attack(LinkedQueue<unit*>& AttackedUnits)
{
	LinkedQueue<unit*> tempList; // queue for the rest (Gunnery)
	ArrayStack<unit*> tempListStack; // Stack For Tanks


	int cap = AttackCapacity;

	// Assumption Pick Gunnery First

	while (cap > 0) 
	{
		unit* tempG = nullptr;
		unit* tempT = nullptr;

		tempG = game->PickUnit(unit::EG);

		if (tempG) // Assumption Gunnery Before Tank
		{

			if (tempG->getAttacked(this))
			{
				game->AddToKilled(tempG);
			}
			else
			{
				tempList.enqueue(tempG);

			}
			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(tempG); // ADD unit to Print List
			cap--;
		}

		if (cap > 0) 
			tempT = game->PickUnit(unit::ET); // Pick Tank in case there still capacity left

		if (tempT)
		{
			if (tempT->getAttacked(this)) // If unit Died will return true
			{
				game->AddToKilled(tempT);
			}
			else if (tempT->CanJoinUML())
			{
				game->AddtoUML(tempT);
			}
			else
				tempListStack.push(tempT);

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(tempT); // ADD unit to Print List
			cap--;
		}

		if (!tempT && !tempG)
			break;		//nothing to Attack // Break the Loop


	}


	while (!tempList.isEmpty()) // return from templist to original lists
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}

	while (!tempListStack.isEmpty()) {
		unit* temp;
		tempListStack.pop(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
