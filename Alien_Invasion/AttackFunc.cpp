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
			temp = game->PickUnit(unit::AS);
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


bool eTank::attack(LinkedQueue<int> & BattleIDs)
{
	LinkedQueue<unit*> tempList;
	int cap = AttackCapacity;

	BattleIDs.enqueue( this->getID() );
	while (cap) {
		unit* temp;
		temp = game->PickUnit(unit::AM);

		if (!temp) // Case Theres no Monsters To Attack
			break;

		if (temp->getAttacked(this)) {

			game->AddToKilled(temp);
			temp->setTD(game->GetTS());

		}


		else {
			tempList.enqueue(temp);
			if (temp->getTa() == -1) temp->setTa(game->GetTS());

		}

		BattleIDs.enqueue(temp->getID());
		cap--;
	}




	while (!tempList.isEmpty()) {
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}
	return true;

}






//Alien Attack

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


bool aMonster::attack() {
	if (isDead()) return false;//No need
	
	else {
		LinkedQueue<unit*>tempList;
		int cap = AttackCapacity;
		while (cap) {
			unit* tempS;
			unit* tempT;
			tempS = game->PickUnit(unit::ES);
			tempT = game->PickUnit(unit::ET);

			if (!tempT && !tempS)
				break;


			if ( tempS) {
				if (tempS->getAttacked(this)) {
					game->AddToKilled(tempS);
					tempS->setTD(game->GetTS());
				}
				else {
					tempList.enqueue(tempS);
					if (tempS->getTa() == -1)tempS->setTa(game->GetTS());

				}

				game->AddAttacked(AM, tempS->getID());
				cap--;
			}

			if (tempT&&cap) {
				
					if (tempT->getAttacked(this)) {
						game->AddToKilled(tempT);
						tempT->setTD(game->GetTS());
					}
					else {
						tempList.enqueue(tempT);
						if (tempT->getTa() == -1)tempT->setTa(game->GetTS());

					}

					game->AddAttacked(AM, tempT->getID());
					cap--;
			}


		}
		while (!tempList.isEmpty()) {
			unit* temp;
			tempList.dequeue(temp);
			game->AddUnit(temp);
		}
		return true;
	}
 }
