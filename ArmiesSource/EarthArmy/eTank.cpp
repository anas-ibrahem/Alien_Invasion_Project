#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"
#include "..\..\Game\Game.h"



eTank::eTank(int id, int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id, ET, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eTank::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*> tempList; // queue temp list
	int cap = AttackCapacity;
	bool AttackSoldiers = 1; // Should Be implemented Discuss With KIMO Related to outputfile

	while (cap > 0) 
	{

		unit* tempM = nullptr;
		unit* tempS = nullptr;

		tempM = game->PickUnit(unit::AM);

		if (tempM) // Assumption Monster Before Soldiers
		{

			if (tempM->getAttacked(this))
			{
				game->AddToKilled(tempM);
			}
			else
			{
				tempList.enqueue(tempM);
				if (tempM->getTa() == -1)
					tempM->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempM->getID());
			cap--;
		}

		if (AttackSoldiers && cap > 0) tempS = game->PickUnit(unit::AS);

		if (tempS) {

			if (tempS->getAttacked(this))
			{
				game->AddToKilled(tempS);
			}
			else {
				tempList.enqueue(tempS);
				if (tempS->getTa() == -1)
					tempS->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempS->getID());
			cap--;

			AttackSoldiers = 1; // Check Condition Again
		}


		if (!tempM && !tempS)
			break;
	}

	while (!tempList.isEmpty()) // return from templist to original lists
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
