#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"

int aMonster::LastMonsterID = 5001;

aMonster::aMonster(int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(LastMonsterID++ , AM , Tj, Health, AttackCapacity, AttackPower)
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
