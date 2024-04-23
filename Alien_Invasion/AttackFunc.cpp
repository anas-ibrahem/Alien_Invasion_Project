#include"../Game/Game.h"

// =================Attack Functions=====================

//Earth Attack
//	bool attack(LinkedQueue<int>& AttackedIDs);


bool eSoldier::attack(LinkedQueue<int>& AttackedIDs) {

		LinkedQueue<unit*>tempList;
		int cap = AttackCapacity;

		while (cap) {

			unit* temp;
			temp = game->PickUnit(unit::AS);

			if (!temp)
				break;

			if (temp->getAttacked(this)) {

				game->AddToKilled(temp); // If Unit Died MOVE IT TO KILLED LIST
				temp->setTD(game->GetTS()); // SET TIME DESTRUCTION

			}
			else {
				tempList.enqueue(temp); // Else Move it to templist
				if (temp->getTa() == -1) // if first time to be attacked set Ta
					temp->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(temp->getID()); // ADD ID to Print List
			cap--;

		}

		while (!tempList.isEmpty()) // return units from templist to its original list
		{
			unit* temp;
			tempList.dequeue(temp);
			game->AddUnit(temp); 
		}


		return (cap < AttackCapacity);

}


bool eHeal::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;

	while (cap) {

		unit* temp;
		temp = game->PickUML();

		if (!temp)
			break;
		if (game->GetTS() - temp->getTd() >= 10)
		{
			game->AddToKilled(temp); //if she takes more than requierd time it moves to killed list
			temp->setTD(game->GetTS()); // SET TIME DESTRUCTION
		}
		else {
			if (temp->getHealed(this)) {
				game->AddUnit(temp); // If Unit Already got maximum healing
				temp->setTD(-1); // return Td to its original value
			}
			else {
				tempList.enqueue(temp); // Else Move it to templist
			}

			AttackedIDs.enqueue(temp->getID()); // ADD ID to Print List
		cap--;
		}
	}

	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->checkUML(temp);
	}

	if (cap != AttackCapacity)
	{
		Health = 0;
		game->AddToKilled(this);
		return true;
	}
	else
	{
		game->AddUnit(this);
		return false;
	}
}

bool eGunnery::attack(LinkedQueue<int>& AttackedIDs) {

	LinkedQueue<unit*>tempList;
	int cap = AttackCapacity;
	int capD = ceil(AttackCapacity / 2);
	int capM = AttackCapacity - capD;
	while (cap) {
		unit* tempDf=NULL;
		unit* tempDr=NULL;
		unit* tempM=NULL;
		if(capD){
			tempDf = game->PickUnit(AD, 'f');//pick drone from front
			if(cap>=2)//make sure that capaceit at least 2 to pick from rear
			tempDr = game->PickUnit(AD, 'r');//pick drone from rear
		}
		if(capM){
			tempM = game->PickUnit(AM);//pick random monster
		}
		
		if (!tempDf && !tempDr && !tempM)//If lists got empty
			break;
	
		if (!tempDf && !tempDr)//If drone list got empty the rest of capacity will go for monster attack
		{
			capM += capD;
			capD = 0;
		}

		if (!tempM )//If Monster list got empty the rest of capacity will go for drone attack
		{
			capD += capM;
			capM = 0;
		}

		if (tempDf&& capD) {
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
			capD--;
			cap--;
		}

		if (tempDr && capD) {
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

		if (tempM && capM) {
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
			capM--;
			cap--;
		}


	}
	while (!tempList.isEmpty()) // return units from templist to its original list
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}

bool eTank::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*> tempList;
	int cap = AttackCapacity;
	bool AttackSoldiers = 1 ; // Should Be implemented Discuss With KIMO Related to outputfile

	while (cap) {

		unit* tempM;
		unit* tempS = nullptr;

		tempM = game->PickUnit(unit::AM);

		if (AttackSoldiers) tempS = game->PickUnit(unit::AS);

		if (!tempM && !AttackSoldiers)
			break;
		if (!tempM && AttackSoldiers && !tempS)
			break;

		if (tempM) // Assumption Gunnery Before Tank
		{
	
			if (tempM->getAttacked(this))
			{
				game->AddToKilled(tempM);
			}
			else
			{
				tempList.enqueue(tempM);
				if (tempM->getTa() == -1)
					tempM->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempM->getID());
			cap--;
		}


		if (tempS && cap > 0 && AttackSoldiers) {

			if (tempS->getAttacked(this))
			{
				game->AddToKilled(tempS);
			}
			else {
				tempList.enqueue(tempS);
				if (tempS->getTa() == -1)
					tempS->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempS->getID());
			cap--;

			AttackSoldiers = 1; // Check Condition Again
		}


	}


	while (!tempList.isEmpty()) // return from templist to original lists
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}






//Alien Attack
//
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


bool aMonster::attack(LinkedQueue<int>& AttackedIDs) {
		LinkedQueue<unit*>tempList;
		int cap = AttackCapacity;
		while (cap) {
			unit* tempS;
			unit* tempT;
			tempS = game->PickUnit(unit::ES);
			tempT = game->PickUnit(unit::ET);

			if (!tempT && !tempS)
				break;

			if (tempT) {
				
					if (tempT->getAttacked(this)) {
						game->AddToKilled(tempT);
					}
					else if (!game->checkUML(tempT)) {
						tempList.enqueue(tempT);
						if (tempT->getTa() == -1)tempT->setTa(game->GetTS());

					}

					AttackedIDs.enqueue(tempT->getID());
					cap--;
			} 

			if (tempS && cap) {
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


		}
		while (!tempList.isEmpty()) {
			unit* temp;
			tempList.dequeue(temp);
			game->AddUnit(temp);
		}
		return (cap<AttackCapacity);
 }



bool aDrone::attack(LinkedQueue<int>& AttackedIDs) { 

	LinkedQueue<unit*> tempList;
	int cap = AttackCapacity;

	while (cap) {

		unit* tempG;
		unit* tempT;
		tempG = game->PickUnit(unit::EG);
		tempT = game->PickUnit(unit::ET);

		if (!tempT && !tempG)
			break;		//nothing to Attack

		if (tempG) // Assumption Gunnery Before Tank
		{

			if (tempG->getAttacked(this))
			{
				game->AddToKilled(tempG);
			}
			else 
			{
				tempList.enqueue(tempG);
				if (tempG->getTa() == -1) 
					tempG->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempG->getID());
			cap--;
		}

		if (tempT && cap > 0) {

			if (tempT->getAttacked(this)) 
			{
				game->AddToKilled(tempT);
			}
			else if (!game->checkUML(tempT)) {
				tempList.enqueue(tempT);
				if (tempT->getTa() == -1)
					tempT->setTa(game->GetTS());

			}

			AttackedIDs.enqueue(tempT->getID());
			cap--;
		}


	}
	while (!tempList.isEmpty()) // return from templist to original lists
	{
		unit* temp;
		tempList.dequeue(temp);
		game->AddUnit(temp);
	}


	return (cap < AttackCapacity);

}
