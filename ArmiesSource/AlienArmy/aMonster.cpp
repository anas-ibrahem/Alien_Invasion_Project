#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"


aMonster::aMonster(int id ,int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(id  , AM , Tj, Health, AttackCapacity, AttackPower)
{
	

}

aMonster::aMonster() : unit(10 , AM , 10, 10 , 10 , 10)
{


}

int aMonster::GetId() 
{
	return id;
}


bool aMonster::attack()
{

	return 1;

}
