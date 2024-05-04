#include "..\ArmiesHeaders\unit.h"
#include "..\Game\Game.h"

unit::unit(int id, UnitType type, int Tj, double Health, int AttackCapacity, double AttackPower, Game* game)
	: type(type), id(id), Tj(Tj), Health(Health), AttackCapacity(AttackCapacity), AttackPower(AttackPower), game(game)
{
	intialHealth = Health;
	Ta = -1;
	Td = -1;
}


bool unit::getAttacked(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead()) // Won't Be Actually in use "Won't attack A dead Unit in any case "
		return false;

	if (reduceHealth(Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health)))) {
		Td = game->GetTS();
	 }
	if (Ta == -1) {
		Ta = game->GetTS();
	}
	return isDead();
}

bool unit::getHealed(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead()) // Won't Be Actually in use "Won't attack A dead Unit in any case "
		return false;

	double amount = Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health));
	Health += amount;
	if (HealthPercent()>20)
	{
		return true; // True if unit has done healing
	}
	return false;
}

bool unit::isDead() const
{
	return (Health == 0) ;
}

double unit::getHealth() const
{
	return Health;
}

double unit::HealthPercent() const
{
	return Health * 100 / intialHealth;
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

void unit::setTD(int T)
{
	Td = T;
}

int unit::getTa() const
{
	return Ta;
}

int unit::getTd() const
{
	return Td;
}

int unit::getTj() const
{
	return Tj;
}

void unit::setTa(int T)
{
	Ta = T;
}
