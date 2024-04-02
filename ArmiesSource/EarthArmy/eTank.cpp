#include "..\..\ArmiesHeaders\EarthArmy\eTank.h"

int eTank::LastTankID = 1001;

eTank::eTank(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastTankID++, ET, Tj, Health, AttackCapacity, AttackPower)
{


}

eTank::eTank() : unit(10, ET, 10, 10, 10, 10)
{


}
bool eTank::attack()
{
	return false;
}
