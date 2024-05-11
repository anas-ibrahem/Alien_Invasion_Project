#pragma once
#include "../Army.h"
#include "../AlliedArmy/alSaver.h"


class AlliedArmy : public Army {
private:

	//Lists of The Army
	LinkedQueue<unit*> Savers;

	//Print ID and Lists of Current Army Attack
	int SU_AttackerID;
	LinkedQueue<unit*> SU_Attacked;


public:

	AlliedArmy();

	//Print Functions
	void PrintAliveUnits();
	bool PrintFights();
	void PrintFight(unit::UnitType type);

	//Lists Control
	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear

	//Getters
	int GetUnitCount(unit::UnitType type);

	//Army Functions
	void clearArmy();
	void attack();

	~AlliedArmy();

};