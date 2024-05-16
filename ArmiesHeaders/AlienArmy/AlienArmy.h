#pragma once
#include "aDrone.h"
#include "aSoldier.h"
#include "aMonster.h"
#include "../Army.h"



class AlienArmy : public Army {
private:

	//Lists of The Army
	char LastAddedAD;
	DoubleLinkedQueue<unit*> Drones;
	LinkedQueue<unit*> Soldiers;
	DynamicArray<unit*> Monster;

	//Print ID and Lists of Current Army Attack
	int AS_AttackerID;
	int AM_AttackerID;
	int AD_AttackerID_Front;
	int AD_AttackerID_Rear;
	LinkedQueue<unit*> AS_Attacked;
	LinkedQueue<unit*> AM_Attacked;
	LinkedQueue<unit*> AD_Attacked_Front;
	LinkedQueue<unit*> AD_Attacked_Rear;


public :
	AlienArmy();

	//Lists Control
	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear

	//Print Functions
	void PrintAliveUnits();
	bool PrintFights();
	void PrintFight(unit::UnitType type);

	//Getters
	int GetUnitCount(unit::UnitType type);

	//Army Functions
	void attack();

	~AlienArmy();

};