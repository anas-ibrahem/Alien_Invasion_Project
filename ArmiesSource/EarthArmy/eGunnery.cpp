#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"



eGunnery::eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(id , EG, Tj, Health, AttackCapacity, AttackPower)
{


}

eGunnery::eGunnery() : unit(10, EG, 10, 10, 10, 10)
{


}

bool eGunnery::attack()
{
    return false;
}
