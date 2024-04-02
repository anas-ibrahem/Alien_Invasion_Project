#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"

int eGunnery::LastGunneryID = 2001;

eGunnery::eGunnery(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastGunneryID++, AD, Tj, Health, AttackCapacity, AttackPower)
{


}

eGunnery::eGunnery() : unit(10, AD, 10, 10, 10, 10)
{


}

bool eGunnery::attack()
{
    return false;
}
