#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"



eSolider::eSolider(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastEarthUnit++, ES, Tj, Health, AttackCapacity, AttackPower)
{


}

eSolider::eSolider() : unit(10, ES, 10, 10, 10, 10)
{


}
bool eSolider::attack()
{
	return false;
}
