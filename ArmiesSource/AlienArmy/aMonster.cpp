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
	while (cap) {
		unit* tempS = NULL;
		unit* tempT = NULL;

		tempS = game->PickUnit(unit::ES);
		if (cap >= 2)//check if capacity can offer another one 
			tempT = game->PickUnit(unit::ET);

		if (!tempT && !tempS)
			break;

		if (tempT) {

			if (tempT->getAttacked(this)) {
				game->AddToKilled(tempT);
			}
			else if (!game->checkUML(tempT)) {
				tempListStack.push(tempT);
				if (tempT->getTa() == -1)tempT->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempT->getID());
			cap--;
		}

		if (tempS) {
			if (tempS->getAttacked(this)) {
				game->AddToKilled(tempS);
			}
			else if (!game->checkUML(tempS)) {
				tempList.enqueue(tempS);
				if (tempS->getTa() == -1)tempS->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempS->getID());
			cap--;
		}
		else if (tempS) game->AddUnit(tempS);


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

