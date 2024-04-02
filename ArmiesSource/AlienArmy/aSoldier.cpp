#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"

int aSolider::LastSoliderID = 3001;

aSolider::aSolider(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastSoliderID++, AS, Tj, Health, AttackCapacity, AttackPower)
{


}

aSolider::aSolider() : unit(10, AS, 10, 10, 10, 10)
{


}
bool aSolider::attack()
{
	return false;
}
