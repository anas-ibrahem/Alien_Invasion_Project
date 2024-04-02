#include "..\ArmiesHeaders\unit.h"

unit::unit(int id, UnitType type, int Tj, int Health, int AttackCapacity, int AttackPower)
	: type(type) , id(id) , Tj(Tj) , Health(Health) , AttackCapacity(AttackCapacity) , AttackPower(AttackPower)
{
	Ta = -1;
}


bool unit::defend(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead())
		return false;
	Health -= Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health));
	return true;
}

bool unit::isDead() const
{
	return (Health == 0) ;
}

int unit::getHealth() const
{
	return Health;
}

int unit::getPower() const
{
	return AttackPower;
}

UnitType unit::GetType() const
{
	return type;
}
