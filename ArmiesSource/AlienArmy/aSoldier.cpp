#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"
#include "..\..\Game\Game.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower,game)
{


}



bool aSoldier::attack(LinkedQueue<int>& AttackedIDs) {

	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	while (cap) {
		unit* temp;
		temp = game->PickUnit(unit::ES);
		if (!temp)
			break;
		if (temp->getAttacked(this)) {
			game->AddToKilled(temp);
			temp->setTD(game->GetTS());

		}
		else if (!game->checkUML(temp)) {
			tempList.enqueue(temp);
			if (temp->getTa() == -1)temp->setTa(game->GetTS());

		}

		AttackedIDs.enqueue(temp->getID());
		cap--;
	}
	while (!tempList.isEmpty()) {
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}
	return(cap < AttackCapacity);
}
