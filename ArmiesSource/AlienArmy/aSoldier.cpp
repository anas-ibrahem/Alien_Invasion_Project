#include "..\..\ArmiesHeaders\AlienArmy\aSoldier.h"


aSoldier::aSoldier(int id ,int Tj, int Health, int AttackCapacity, int AttackPower) :
	unit(id , AS, Tj, Health, AttackCapacity, AttackPower)
{


}





bool aSoldier::attack()
{
	return false;
}
