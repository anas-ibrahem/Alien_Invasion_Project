#include "..\..\ArmiesHeaders\EarthArmy\eSoldier.h"



eSoldier::eSoldier(int id , int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(id , ES, Tj, Health, AttackCapacity, AttackPower)
{


}



bool eSoldier::attack()
{
	return false;
}
