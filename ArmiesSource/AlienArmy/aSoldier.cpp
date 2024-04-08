#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower, Game* game) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower,game)
{


}





bool aSoldier::attack()
{
	return false;
}
