#pragma once
#include "../Army.h"
#include "eSoldier.h"
#include "eTank.h"
#include "eGunnery.h"
#include "eHeal.h"


class EarthArmy : public Army {
private:
	//Lists of The Army
	LinkedQueue<unit*> Soldiers;
	ArrayStack<unit*> Tanks;
	priQueue<unit*>Gunneries ;
	ArrayStack<unit*> Healers;
	priQueue<unit*> UML;

	//Print ID and Lists of Current Army Attack
	int ET_AttackerID;
	int ES_AttackerID;
	bool ES_Attacker_Infected;
	int EG_AttackerID;
	int EH_AttackerID;
	LinkedQueue<unit*> ET_Attacked;
	LinkedQueue<unit*> ES_Attacked;
	LinkedQueue<unit*> EG_Attacked;
	LinkedQueue<unit*> EH_Attacked;

	//Inf Percentage
	double InfPercentage;
	double InfThersholdPercentage;


public:

	EarthArmy();

	//Print Functions
	void PrintAliveUnits();
	bool PrintFights();
	void PrintFight(unit::UnitType type);

	//Getters
	int GetUnitCount(unit::UnitType type);
	int GetUMLCount();
	double GetInfPercentage() const;

	//Setters & Calculate
	void SetInfThershold(double perc);
	void CalcInfPercentage();
	
	//Lists Control
	bool AddUnit(unit* unit, char InsertDir = 'n'); // n for nonsent f for front r for rear
	bool AddtoUML(unit* unit);
	unit* PickfromUML();
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear

	//Army Functions
	void attack();
	bool CallAllied();
	void SpreadInfection();



	~EarthArmy();

};