#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../Army.h"



class AlienArmy : public Army {
private:
	char LastAddedAD;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	DynamicArray<unit*> Monster;

	int AS_AttackerID;
	int AM_AttackerID;
	int AD_AttackerID_Front;
	int AD_AttackerID_Rear;

	LinkedQueue<int> AS_Attacked;
	LinkedQueue<int> AM_Attacked;
	LinkedQueue<int> AD_Attacked_Front;
	LinkedQueue<int> AD_Attacked_Rear;

public :
	AlienArmy();
	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	void PrintAliveUnits();

	bool PrintFights();
	void PrintFight(unit::UnitType type);

	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear
	void attack();
	int GetUnitCount(unit::UnitType type);
	~AlienArmy();

};