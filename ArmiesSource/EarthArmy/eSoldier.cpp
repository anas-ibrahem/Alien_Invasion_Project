#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"

int eSolider::LasteSoliderID = 1;

eSolider::eSolider(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LasteSoliderID++, ES, Tj, Health, AttackCapacity, AttackPower)
{


}

eSolider::eSolider() : unit(10, ES, 10, 10, 10, 10)
{


}
bool eSolider::attack()
{
	return false;
}
