#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"



eTank::eTank(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastEarthUnit++, ET, Tj, Health, AttackCapacity, AttackPower)
{


}

eTank::eTank() : unit(10, ET, 10, 10, 10, 10)
{


}
bool eTank::attack()
{
	return false;
}
