#include "..\..\ArmiesHeaders\AlienArmy\aDrone.h"


aDrone::aDrone(int id , int Tj , int Health , int AttackCapacity , int AttackPower, Game* game) :
	unit(id , AD , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}

int aDrone::GetId() // For testing Purpose  // Anas
{
	return id;
}


bool aDrone::attack()
{

	return 1;

}
