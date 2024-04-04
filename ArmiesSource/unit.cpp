#include "..\ArmiesHeaders\unit.h"
int unit::LastAlienUnit = 2001;
int unit::LastEarthUnit = 1;

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

bool unit::reduceHealth(int amount)
{
	Health -= amount;
	if (Health <= 0)
	{
		Health = 0;
		return true;
	}
	return false;
}

int unit::getPower() const
{
	return AttackPower;
}

int unit::getID() const
{
	return id;
}

UnitType unit::GetType() const
{
	return type;
}
