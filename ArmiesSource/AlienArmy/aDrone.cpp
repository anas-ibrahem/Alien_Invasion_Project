#include "..\..\ArmiesHeaders\AlienArmy\aDrone.h"

int aDrone::LastDroneID = 6001;

aDrone::aDrone(int Tj , int Health , int AttackCapacity) :
	unit(LastDroneID++ , AD , Tj, Health, AttackCapacity)
{
	

}

aDrone::aDrone() : unit(10 , AD , 10, 10 , 10 , 10)
{


}

bool aDrone::defend()
{


	return 1;
}

int aDrone::GetId() // For testing Purpose  // Anas
{
	return id;
}


bool aDrone::attack()
{

	return 1;

}
