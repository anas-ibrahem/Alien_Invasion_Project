#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"
#include "..\..\Game\Game.h"


aMonster::aMonster(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id  , AM , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}

bool aMonster::attack(LinkedQueue<int>& AttackedIDs) {
	LinkedQueue<unit*>tempList;
	ArrayStack<unit*>tempListStack;
	int cap = AttackCapacity;
	while (cap > 0) {
		unit* tempS = nullptr;
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

			AttackedIDs.enqueue(tempT->getID());
			cap--;
		}


		if (cap > 0)//check if capacity can offer another one 
			tempS = game->PickUnit(unit::ES);

		if (tempS) 
		{
			if (WillInfect())
			{
				tempS->setInfected(true);
				tempList.enqueue(tempS);
			} 
			else if (tempS->getAttacked(this)) 
					game->AddToKilled(tempS);

			else if (!game->AddUML(tempS)) 
					tempList.enqueue(tempS);

			AttackedIDs.enqueue(tempS->getID());
			cap--;
		}
		

		if (!tempT && !tempS)
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


bool aMonster::WillInfect() const
{
	int ProbGen = rand() % 100 + 1;
	return (ProbGen <= game->GetInfectProb());
}