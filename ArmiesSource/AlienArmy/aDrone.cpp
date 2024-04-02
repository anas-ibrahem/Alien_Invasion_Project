#include "..\..\ArmiesHeaders\AlienArmy\aDrone.h"

int aDrone::LastDroneID = 4001;

aDrone::aDrone(int Tj , int Health , int AttackCapacity , int AttackPower) :
	unit(LastDroneID++ , AD , Tj, Health, AttackCapacity, AttackPower)
{
	

}

aDrone::aDrone() : unit(10 , AD , 10, 10 , 10 , 10)
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
