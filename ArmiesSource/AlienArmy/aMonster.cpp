#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"
#include "..\..\Game\Game.h"


double aMonster::AM_Infect_Prob = 0;

aMonster::aMonster(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id  , AM , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}

bool aMonster::attack(LinkedQueue<unit*>& AttackedUnits) {

	LinkedQueue<unit*>tempList;
	ArrayStack<unit*>tempListStack; // For Tanks

	int cap = AttackCapacity;
	while (cap > 0) {
		unit* tempES = nullptr;
		unit* tempSU = nullptr;
		unit* tempT = nullptr;

		tempT = game->PickUnit(unit::ET);

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
				AttackedUnits.enqueue(tempT);
			cap--;
		}


		if (cap > 0)//check if capacity can offer another one 
			tempES = game->PickUnit(unit::ES);

		if (tempES) 
		{
			// Don't infect if already infected or immuned
			if (WillInfect() && !tempES->isInfected() && !tempES->isImmuned()) 
			{
				tempES->setInfected(true);
				tempList.enqueue(tempES);
			} 

			else if (tempES->getAttacked(this))  // if unit died will return true
					game->AddToKilled(tempES);

			else if (tempES->CanJoinUML())
			{
				game->AddToKilled(tempES);
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
				game->AddToKilled(tempSU);

			else
				tempList.enqueue(tempSU);

			if (game->GetMode() == 'a')
				AttackedUnits.enqueue(tempSU);

			cap--;
		}
		

		if (!tempT && !tempES && !tempSU)
			break; 
				//nothing to Attack // Break the Loop
	}

	while (!tempList.isEmpty()) {
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

void aMonster::set_AM_Infect_Prob(double prob)
{
	AM_Infect_Prob = prob;
}


bool aMonster::WillInfect() const
{
	int ProbGen = rand() % 100 + 1;
	return (ProbGen <= AM_Infect_Prob );
}