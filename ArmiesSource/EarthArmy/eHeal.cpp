#include "..\..\ArmiesHeaders\EarthArmy\eHeal.h"
#include "..\..\Game\Game.h"



eHeal::eHeal(int id ,int Tj, double Health, int AttackCapacity, double AttackPower, Game* game) :
	unit(id , EH, Tj, Health, AttackCapacity, AttackPower,game)
{


}


bool eHeal::attack(LinkedQueue<int>& AttackedIDs)
{
	LinkedQueue<unit*> tempList; // Queue to Store Templist
	int cap = AttackCapacity;

	while (cap > 0) 
	{

		unit* temp = nullptr;
		temp = game->PickUML();


		if (temp)
		{
			if (game->GetTS() - temp->getTd() >= 10)
			{
				game->AddToKilled(temp); //if unit spent more than Limit time it moves to killed list
				temp->setTD(game->GetTS()); // SET TIME DESTRUCTION
			}
			else
			{
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

		if (!temp)
			break;


	}



	while (!tempList.isEmpty()) // return units from templist to uml list again
	{
		unit* temp;
		tempList.dequeue(temp);
		game->checkUML(temp);
	}

	if (cap != AttackCapacity)
	{
		Health = 0;
		Ta = game->GetTS(); //SET TIME ATTACKED WHEN SHE HEALS ANY UNIT AND GET KILLED
		Td = Ta; //SET DESTRUCTION TIME , USING Ta TO NOT CALL THE FUNCTION AGAIN
		game->AddToKilled(this); //AFTER HEALING ... HEALER MOVED TO KILLED LIST
		return true;
	}
	else
	{
		game->AddUnit(this); //IF SHE DOESNT HEAL ANY UNIT MOVE BACK TO THE GAME
		return false;
	}


}