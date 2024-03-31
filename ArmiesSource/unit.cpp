#include "..\ArmiesHeaders\unit.h"

unit::unit(int id, UnitType type, int Tj, int Ta, int Health, int AttackCapacity)
	: type(type) , id(id) , Tj(Tj) , Ta(Ta) , Health(Health) , AttackCapacity(AttackCapacity)
{

}


bool unit::isDead()
{
	return (Health == 0) ;
}

UnitType unit::GetType() const
{
	return type;
}
