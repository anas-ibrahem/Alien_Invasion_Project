#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"
#include "..\..\Game\Game.h"



eGunnery::eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , EG, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eGunnery::attack(LinkedQueue<int>& AttackedIDs) {

	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	int capD = ceil(AttackCapacity / 2);
	int capM = AttackCapacity - capD;

	while (cap) {
		unit* tempDf = NULL;
		unit* tempDr = NULL;
		unit* tempM = NULL;
		if (capD) {
			tempDf = game->PickUnit(AD, 'f');//pick drone from front
			if (capD >= 2)//make sure that capaceit at least 2 to pick from rear
				tempDr = game->PickUnit(AD, 'r');//pick drone from rear
		}
		if (capM) {
			tempM = game->PickUnit(AM);//pick random monster
		}

		if (!tempDf && !tempDr && !tempM)//If lists got empty
			break;

		if (!tempDf && !tempDr)//If drone list got empty the rest of capacity will go for monster attack
		{
			capM += capD;
			capD = 0;
		}

		if (!tempM)//If Monster list got empty the rest of capacity will go for drone attack
		{
			capD += capM;
			capM = 0;
		}

		if (tempDf && capD) {
			if (tempDf->getAttacked(this)) {

				game->AddToKilled(tempDf); // If Unit Died MOVE IT TO KILLED LIST
				tempDf->setTD(game->GetTS()); // SET TIME DESTRUCTION

			}
			else {
				tempList.enqueue(tempDf); // Else Move it to templist
				if (tempDf->getTa() == -1) // if first time to be attacked set Ta
					tempDf->setTa(game->GetTS());

			}
			AttackedIDs.enqueue(tempDf->getID());
			capD--;
			cap--;
		}

		if (tempDr && capD) {
			if (tempDr->getAttacked(this)) {

				game->AddToKilled(tempDr); // If Unit Died MOVE IT TO KILLED LIST
				tempDr->setTD(game->GetTS()); // SET TIME DESTRUCTION

			}
			else {
				tempList.enqueue(tempDr); // Else Move it to templist
				if (tempDr->getTa() == -1) // if first time to be attacked set Ta
					tempDr->setTa(game->GetTS());

			}
			AttackedIDs.enqueue(tempDr->getID());
			cap--;
		}

		if (tempM && capM) {
			if (tempM->getAttacked(this)) {

				game->AddToKilled(tempM); // If Unit Died MOVE IT TO KILLED LIST
				tempM->setTD(game->GetTS()); // SET TIME DESTRUCTION

			}
			else {
				tempList.enqueue(tempM); // Else Move it to templist
				if (tempM->getTa() == -1) // if first time to be attacked set Ta
					tempM->setTa(game->GetTS());

			}
			AttackedIDs.enqueue(tempM->getID());
			capM--;
			cap--;
		}


	}
	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}