#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"

int aMonster::LastMonsterID = 5001;

aMonster::aMonster(int Tj , int Health , int AttackCapacity) :
	unit(LastMonsterID++ , AD , Tj, Health, AttackCapacity)
{
	

}

aMonster::aMonster() : unit(10 , AD , 10, 10 , 10 , 10)
{


}

bool aMonster::defend()
{


	return 1;
}

int aMonster::GetId() 
{
	return id;
}


bool aMonster::attack()
{

	return 1;

}
