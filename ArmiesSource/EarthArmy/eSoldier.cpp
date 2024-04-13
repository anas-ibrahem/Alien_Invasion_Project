#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"



eSoldier::eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , ES, Tj, Health, AttackCapacity, AttackPower,game)
{
}

bool eSoldier::attack()
{
	return false;
}

