#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"


aSolider::aSolider(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastAlienUnit++, AS, Tj, Health, AttackCapacity, AttackPower)
{


}

aSolider::aSolider() : unit(10, AS, 10, 10, 10, 10)
{


}
bool aSolider::attack()
{
	return false;
}
