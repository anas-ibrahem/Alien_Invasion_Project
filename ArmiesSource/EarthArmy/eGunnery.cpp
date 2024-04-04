#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"



eGunnery::eGunnery(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastEarthUnit++, EG, Tj, Health, AttackCapacity, AttackPower)
{


}

eGunnery::eGunnery() : unit(10, EG, 10, 10, 10, 10)
{


}

bool eGunnery::attack()
{
    return false;
}
