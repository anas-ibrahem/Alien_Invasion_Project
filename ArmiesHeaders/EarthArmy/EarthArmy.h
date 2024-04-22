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

	LinkedQueue<int> ET_Attacked;
	LinkedQueue<int> ES_Attacked;
	LinkedQueue<int> EG_Attacked;
	LinkedQueue<int> EH_Attacked;

public:
	EarthArmy();
	bool AddUnit(unit* unit);
	void PrintAliveUnits();

	bool PrintFights();
	void PrintFight(unit::UnitType type);

	unit* PickUnit(unit::UnitType type , char dronedir = 'f');
	bool AddtoUML(unit* unit);
	unit* PickfromUML();
	void attack();
	~EarthArmy();

};