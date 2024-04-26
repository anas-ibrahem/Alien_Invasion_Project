#include "..\..\ArmiesHeaders\EarthArmy\eHeal.h"
#include "..\..\Game\Game.h"



eHeal::eHeal(int id ,int Tj, double Health, int AttackCapacity, double AttackPower, Game* game) :
	unit(id , EH, Tj, Health, AttackCapacity, AttackPower,game)
{


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