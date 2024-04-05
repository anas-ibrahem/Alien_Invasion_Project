#pragma once
#include <ctime>
#include <cstdlib>
#include "unit.h"
#include "AlienArmy/AlienArmy.h"
#include "EarthArmy/EarthArmy.h"

struct GenParameters {

	int prob;
	int EarthPercentage[3];
	int AlienPercentage[3];
	int A_Health_Range[2];
	int A_Capacity_Range[2];
	int A_Power_Range[2];
	int E_Health_Range[2];
	int E_Capacity_Range[2];
	int E_Power_Range[2];
	

};




class RandGen
{

private :

	GenParameters Data;
	int LastAlienID;
	int LastEarthID;


public:

	RandGen(GenParameters P);
	bool WillGenerate();
	unit* GenerateUnitAlien(int TimeJoin);
	unit* GenerateUnitEarth(int TimeJoin);
	unit* Create(UnitType T, int TimeJoin);
	int ValueRand(int Range[]);

};