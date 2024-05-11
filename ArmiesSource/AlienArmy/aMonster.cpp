#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"
#include "..\..\Game\Game.h"


int aMonster::AM_Infect_Prob = 0;

aMonster::aMonster(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id  , AM , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}

bool aMonster::attack(LinkedQueue<unit*>& AttackedUnits) {

	LinkedQueue<unit*>tempList;
	LinkedQueue<unit*>tempListSU;
	ArrayStack<unit*>tempListStack;
	int cap = AttackCapacity;
	while (cap > 0) {
		unit* tempS = nullptr;
		unit* tempSU = nullptr;
		unit* tempT = nullptr;

		tempT = game->PickUnit(unit::ET);

		if (tempT) 
		{
			if (tempT->getAttacked(this)) {
				game->AddToKilled(tempT);
			}
			else if (!game->AddUML(tempT)) {
				tempListStack.push(tempT);
			}
			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempT);
			cap--;
		}


		if (cap > 0)//check if capacity can offer another one 
			tempS = game->PickUnit(unit::ES);

		if (tempS) 
		{
			// Don't infect if already infected or immuned
			if (WillInfect() && !tempS->isInfected() && !tempS->isImmuned()) 
			{
				tempS->setInfected(true);
				tempList.enqueue(tempS);
			} 

			else if (tempS->getAttacked(this)) 
					game->AddToKilled(tempS);

			else if (!game->AddUML(tempS)) 
					tempList.enqueue(tempS);

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempS);

			cap--;
		}

		if (cap > 0)//check if capacity can offer another one 
			tempSU = game->PickUnit(unit::SU);

		if (tempSU)
		{

			 if (tempSU->getAttacked(this))
				game->AddToKilled(tempS);

			else
				tempListSU.enqueue(tempSU);

			if (game->getMode() == 'a')
				AttackedUnits.enqueue(tempSU);

			cap--;
		}
		

		if (!tempT && !tempS&&!tempSU)
			break; 
				//nothing to Attack // Break the Loop
	}

	while (!tempList.isEmpty()) {
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}

	while (!tempListSU.isEmpty()) {
		unit* temp;
		tempListSU.dequeue(temp);
		game->AddUnit(temp);
	}

	while (!tempListStack.isEmpty()) {
		unit* temp;
		tempListStack.pop(temp);
		game->AddUnit(temp);
	}

	return (cap < AttackCapacity);
}

void aMonster::set_AM_Infect_Prob(int prob)
{
	AM_Infect_Prob = prob;
}


bool aMonster::WillInfect() const
{
	int ProbGen = rand() % 100 + 1;
	return (ProbGen <= AM_Infect_Prob);
}