#include "..\..\ArmiesHeaders\AlienArmy\aMonster.h"


aMonster::aMonster(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id  , AM , Tj, Health, AttackCapacity, AttackPower,game)
{
	

}

int aMonster::GetId() 
{
	return id;
}

