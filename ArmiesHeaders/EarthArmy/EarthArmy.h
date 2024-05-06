#pragma once
#include "../Army.h"
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"
#include "eHeal.h"


class EarthArmy : public Army {
private:
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*>Gunneries ;
	ArrayStack<unit*> Healers;
	priQueue<unit*> UML;

	int ET_AttackerID;
	int ES_AttackerID;
	int EG_AttackerID;
	int EH_AttackerID;

	LinkedQueue<unit*> ET_Attacked;
	LinkedQueue<unit*> ES_Attacked;
	LinkedQueue<unit*> EG_Attacked;
	LinkedQueue<unit*> EH_Attacked;

public:
	EarthArmy();
	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	void PrintAliveUnits();

	bool PrintFights();
	void PrintFight(unit::UnitType type);

	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear
	bool AddtoUML(unit* unit);
	unit* PickfromUML();
	void attack();
	int GetUnitCount(unit::UnitType type);
	int GetUMLCount();
	int GetInfectedCount();

	~EarthArmy();

};