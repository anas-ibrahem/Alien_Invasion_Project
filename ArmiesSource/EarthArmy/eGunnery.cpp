#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"
#include "..\..\Game\Game.h"



eGunnery::eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , EG, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eGunnery::attack(LinkedQueue<int>& AttackedIDs) {

	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	int capD = ceil(AttackCapacity / 2.0);

	while (cap > 0) {
		unit* tempDf = nullptr;
		unit* tempDr = nullptr;
		unit* tempM = nullptr;

		if (capD > 0) {

			tempDf = game->PickUnit(AD, 'f');//pick drone from front
			
			if(tempDf)	capD--; 

			tempDr = game->PickUnit(AD, 'r');//pick drone from rear

			if (tempDr)	capD--;

		}

		if (capD == -1) {

			/*game->AddUnit(tempDf,'f');*/

			/*game->AddUnit(tempDr, 'r');*/
			
		}
		

		if(tempDf) {
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
		
			cap--;
		}

		if (tempDr) {
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

		if (cap > 0)
			tempM = game->PickUnit(unit::AM);

			if (tempM ) {
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
				cap--;
			}



		if (!tempDf && !tempDr && !tempM)//If lists got empty
			break;		


	}
	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}