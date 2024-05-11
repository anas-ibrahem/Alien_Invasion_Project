#pragma once
#include <ctime>
#include <cstdlib>
#include "../ArmiesHeaders/unit.h"
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include "../ArmiesHeaders/EarthArmy/EarthArmy.h"
#include "../ArmiesHeaders/AlliedArmy/AlliedArmy.h"


class Game;

// Struct to Easily Control Data
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
	int AL_Health_Range[2];
	int AL_Capacity_Range[2];
	int AL_Power_Range[2];
	

};




class RandGen
{

private :

	//Gen Needed Data
	GenParameters Data;
	int LastAlienID;
	int LastEarthID;
	int LastAlliedID;

public:

	RandGen(GenParameters P);

	//Generate Functions
	unit* GenerateUnitAlien(int TimeJoin, Game* game);
	unit* GenerateUnitEarth(int TimeJoin,Game*game);
	unit* GenerateUnitAllied(int TimeJoin, Game* game);
	unit* Create(unit::UnitType T, int TimeJoin, Game* game);

	//Helper function
	bool WillGenerate() const;
	int ValueRand(int Range[]);

	~RandGen();

};