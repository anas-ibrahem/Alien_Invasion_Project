#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"
#include "..\..\Game\Game.h"



eTank::eTank(int id, int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id, ET, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eTank::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*> tempList;
	int cap = AttackCapacity;
	bool AttackSoldiers = 1; // Should Be implemented Discuss With KIMO Related to outputfile

	while (cap) {

		unit* tempM;
		unit* tempS = nullptr;

		tempM = game->PickUnit(unit::AM);

		if (AttackSoldiers) tempS = game->PickUnit(unit::AS);

		if (!tempM && !AttackSoldiers)
			break;
		if (!tempM && AttackSoldiers && !tempS)
			break;

		if (tempM) // Assumption Gunnery Before Tank
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


		if (tempS && cap > 0 && AttackSoldiers) {

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
		else if (tempS) game->AddUnit(tempS);


	}


	while (!tempList.isEmpty()) // return from templist to original lists
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
