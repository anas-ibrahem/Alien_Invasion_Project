#include"../Game/Game.h"

//=================================Attack Functions=====================

//Earth Attack

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
			else {
				tempList.enqueue(temp);
				if (temp->getTa() == -1)temp->setTa(game->GetTS());

			}

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












//Army Attack

bool aSoldier::attack() {
	if (isDead()) return false;//No need


	else {
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
			else {
				tempList.enqueue(temp);
				if (temp->getTa() == -1)temp->setTa(game->GetTS());
			
			}
			
			game->AddAttacked(unit::AS, temp->getID());
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
