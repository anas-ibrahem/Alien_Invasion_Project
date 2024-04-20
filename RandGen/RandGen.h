#pragma once
#include <ctime>
#include <cstdlib>
#include "../ArmiesHeaders/unit.h"
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include "../ArmiesHeaders/EarthArmy/EarthArmy.h"

class Game;

struct GenParameters {

	int prob;
	int EarthPercentage[4];
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
	unit* GenerateUnitAlien(int TimeJoin, Game* game);
	unit* GenerateUnitEarth(int TimeJoin,Game*game);
	unit* Create(unit::UnitType T, int TimeJoin, Game* game);
	int ValueRand(int Range[]);

};