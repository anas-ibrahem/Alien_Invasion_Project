#include "..\..\ArmiesHeaders\EarthArmy\eGunnery.h"



eGunnery::eGunnery(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , EG, Tj, Health, AttackCapacity, AttackPower,game)
{


}


bool eGunnery::attack()
{
    return false;
}
