#pragma once
#include "../Army.h"
#include "../AlliedArmy/alSaver.h"


class AlliedArmy : public Army {
private:

	LinkedQueue<unit*> Savers;

	int SU_AttackerID;

	LinkedQueue<unit*> SU_Attacked;


public:
	AlliedArmy();

	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	void PrintAliveUnits();
	bool PrintFights();
	void PrintFight(unit::UnitType type);
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear
	void attack();
	int GetUnitCount(unit::UnitType type);
	void clearArmy();
	~AlliedArmy();

};