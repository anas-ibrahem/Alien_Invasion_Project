#include "..\ArmiesHeaders\unit.h"
#include "..\Game\Game.h"

int unit::Num_Healed = 0;

unit::unit(int id, UnitType type, int Tj, double Health, int AttackCapacity, double AttackPower, Game* game)
	: type(type), id(id), Tj(Tj), Health(Health), AttackCapacity(AttackCapacity), AttackPower(AttackPower), game(game)
{
	Healed = false;
	intialHealth = Health;
	Ta = Tj_UML = Td = -1;

}


bool unit::getAttacked(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead()) // Won't Be Actually in use "Won't attack A dead Unit in any case "
		return false;

	reduceHealth( Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health)) ) ;
		
	if (Ta == -1) // First Time Getting Attacked
		Ta = game->GetTS();


	return isDead();
}

bool unit::getHealed(unit* Attacker)
{
	if (Attacker->isDead() || this->isDead()) // Won't Be Actually in use "Won't attack A dead Unit in any case "
		return false;
	
	//Calculate Amount to be healed
	double amount = Attacker->AttackPower * Attacker->Health / (100 * sqrt(Health));
	//Heal by half amount if Infected ES 
	(isInfected() && type == ES ) ? Health += amount/2 : Health += amount;
	
	//Set unit as Healed (at least once) and Count it
	if (!isHealed())
	{
		Num_Healed++;
		Healed = true;
	}



	if (HealthPercent() > 20)
	{
		//Cure Infected ES and Immune it
		if (type == ES && isInfected())
		{
			setImmuned(true);
			setInfected(false);
		}


		return true; // True if unit has done healing
	}

	return false;
}

bool unit::isDead() const
{
	return (Health == 0) ;
}

bool unit::CanJoinUML() const
{
	return HealthPercent() < 20 && HealthPercent() > 0;
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
			Health = 0;

	return isDead();
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

void unit::setTj_UML(int T)
{
	Tj_UML = T;
}

int unit::getTj_UML() const
{
	return Tj_UML ;
}

bool unit::isHealed() const
{
	return Healed;
}

int unit::GetNumOfHealed()
{
	return Num_Healed;
}


bool unit::isInfected()
{
	return false;
}

bool unit::isImmuned()
{
	return false;
}

void unit::setInfected(bool Infect)
{
}

void unit::setImmuned(bool Immune)
{
}
