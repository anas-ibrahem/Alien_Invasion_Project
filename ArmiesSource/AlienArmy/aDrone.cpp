#include "../ArmiesHeaders/AlienArmy/aDrone.h"

aDrone::aDrone(int id , int Tj , int Ta , int Health , int AttackCapacity) :
	unit(id, "AD", Tj, Ta, Health, AttackCapacity)
{
	

}

aDrone::aDrone() : unit(10 , "AD" , 10, 10 , 10 , 10)
{


}

bool aDrone::defend()
{


	return 1;
}


bool aDrone::attack()
{

	return 1;

}
