#include "..\..\ArmiesHeaders\EarthArmy\eHeal.h"



eHeal::eHeal(int id ,int Tj, double Health, int AttackCapacity, double AttackPower, Game* game) :
	unit(id , EH, Tj, Health, AttackCapacity, AttackPower,game)
{


}