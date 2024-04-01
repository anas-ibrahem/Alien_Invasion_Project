#include "..\ArmiesHeaders\unit.h"

unit::unit(int id, UnitType type, int Tj, int Health, int AttackCapacity, int AttackPower)
	: type(type) , id(id) , Tj(Tj) , Health(Health) , AttackCapacity(AttackCapacity) , AttackPower(AttackPower)
{
	Ta = -1;
}


bool unit::isDead()
{
	return (Health == 0) ;
}

UnitType unit::GetType() const
{
	return type;
}
