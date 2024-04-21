#include "..\ArmiesHeaders\unit.h"

unit::unit(int id, UnitType type, int Tj, double Health, int AttackCapacity, double AttackPower, Game* game)
	: type(type), id(id), Tj(Tj), Health(Health), AttackCapacity(AttackCapacity), AttackPower(AttackPower), game(game)
{
	Ta = -1;
}


bool unit::getAttacked(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead()) // Won't Be Actually in use "Won't attack A dead Unit in any case "
		return false;

	return reduceHealth(Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health)));
	
}

bool unit::isDead() const
{
	return (Health == 0) ;
}

double unit::getHealth() const
{
	return Health;
}

bool unit::reduceHealth(double amount)
{
	Health -= amount;
	if (Health <= 0)
	{
		Health = 0;
		return true; // True if unit died
	}
	return false;
}

double unit::getPower() const
{
	return AttackPower;
}

int unit::getID() const
{
	return id;
}

unit::UnitType unit::GetType() const
{
	return type;
}
