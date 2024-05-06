#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"
#include "..\..\Game\Game.h"



eGunnery::eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , EG, Tj, Health, AttackCapacity, AttackPower,game)
{


}


bool eGunnery::attack(LinkedQueue<unit*>& AttackedUnits)
{
	// Assume Priority for AD always
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	int capD = (cap != 2) ? ceil(AttackCapacity / 2.0) : 2; // Ternary to Handle the case of attackcapacity 2 (Make him pick 2 drones not 2 monsters)

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

		if (capD == -1)  // return drones in case of picking no pair and no single drone was left
		{
			game->AddUnit(tempDf,'f');
			tempDf = nullptr;
			game->AddUnit(tempDr, 'r');
			tempDr = nullptr;
		}
		

		if(tempDf) {
			if (tempDf->getAttacked(this)) {

				game->AddToKilled(tempDf); // If Unit Died MOVE IT TO KILLED LIST
			}
			else {
				tempList.enqueue(tempDf); // Else Move it to templist

			}

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempDf);
		
			cap--;
		}

		if (tempDr) {
			if (tempDr->getAttacked(this)) {

				game->AddToKilled(tempDr); // If Unit Died MOVE IT TO KILLED LIST
			}
			else {
				tempList.enqueue(tempDr); // Else Move it to templist

			}

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempDr);

			cap--;
		}

		if (cap > 0)
			tempM = game->PickUnit(unit::AM);

		if (tempM) {
			if (tempM->getAttacked(this)) 
			{
				game->AddToKilled(tempM); // If Unit Died MOVE IT TO KILLED LIST
			}
			else 
			{
				tempList.enqueue(tempM); // Else Move it to templist

			}			
			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempM);
			cap--;
		}



		if (!tempDf && !tempDr && !tempM)//If lists got empty
			break;		


	}

	char ADInsertdir = 'f'; // Start Inserting from front as we started picking from front

	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		
		if (temp->GetType() == unit::AD) 
		{
			game->AddUnit(temp, ADInsertdir);
			(ADInsertdir == 'f' ? ADInsertdir = 'r' : ADInsertdir = 'f');
			
		}
		else 
			game->AddUnit(temp); // Actually it would ignore the direction in case of AM but just for readability
		
	
	}


	return (cap < AttackCapacity);

}