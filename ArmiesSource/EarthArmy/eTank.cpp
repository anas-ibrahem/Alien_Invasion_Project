#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"
#include "..\..\Game\Game.h"


bool eTank::AttackSoldiers = false;

eTank::eTank(int id, int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id, ET, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eTank::attack(LinkedQueue<unit*>& AttackedUnits)
{
	LinkedQueue<unit*> tempList; // queue temp list
	int cap = AttackCapacity;
	int ES_C = game->GetUnitCount(unit::ES);
	int AS_C = game->GetUnitCount(unit::AS);

	while (cap > 0) 
	{

		if (AS_C == 0) 
			AttackSoldiers = false;
		else if (!AttackSoldiers)
			AttackSoldiers = ES_C * 100.0 / AS_C < 30;
		else
			AttackSoldiers = ES_C * 100.0 / AS_C < 80;


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
			}

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempM); // ADD unit to Print List
			cap--;
		}

		if (AttackSoldiers && cap > 0) tempS = game->PickUnit(unit::AS);

		if (tempS) {

			if (tempS->getAttacked(this))
			{
				AS_C--;// Reduce Count of AS if unit AS died
				game->AddToKilled(tempS);
			}
			else {
				tempList.enqueue(tempS);
			}

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempS); // ADD unit to Print List
			cap--;
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
