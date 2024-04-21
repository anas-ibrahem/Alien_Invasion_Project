#include"../Game/Game.h"

bool eSoldier::attack() {
	if (isDead()) return false;//No need


	else {
		LinkedQueue<unit*>tempList;
		int cap = AttackCapacity;
		while (cap) {
			unit* temp;
			temp=game->PickUnit(unit::AS);
			if (!temp)
				break;
			if (temp->getAttacked(this)) {
				game->AddToKilled(temp);
				temp->setTD(game->GetTS());
				
			}		
			else
			tempList.enqueue(temp);

			game->AddAttacked(unit::ES, temp->getID());
			cap--;
		}
		while (!tempList.isEmpty()) {
			unit* temp;
			tempList.dequeue(temp);
			game->AddUnit(temp);
		}
		return true;
	}

}