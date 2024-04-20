#include "..\..\ArmiesHeaders\EarthArmy\eHeal.h"



eHeal::eHeal(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , EH, Tj, Health, AttackCapacity, AttackPower,game)
{


}


bool eHeal::attack()
{
    return false;
}
