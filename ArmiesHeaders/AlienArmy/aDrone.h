#pragma once
#include "..\unit.h"
class Game;

class aDrone :public unit
{



public :

	aDrone(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game);
	bool attack(LinkedQueue<int>& AttackedIDs, LinkedQueue<int>& InfectedIDS);
};

