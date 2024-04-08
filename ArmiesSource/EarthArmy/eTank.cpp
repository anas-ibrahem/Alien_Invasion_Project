#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"



eTank::eTank(int id, int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id, ET, Tj, Health, AttackCapacity, AttackPower,game)
{


}

bool eTank::attack()
{
	return false;
}
