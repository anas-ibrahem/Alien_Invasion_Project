#pragma once
#include <ctime>
#include <cstdlib>
#include "../Game/Game.h"
#include "../ArmiesHeaders/EarthArmy/EarthArmy.h"
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"

struct ArmyParameter {

	UnitType type;
	int Percentage;

	ArmyParameter()
	{	
		type = ES;    
		Percentage = 0;
	}

};

class RandGen
{
	int n, Prob;
	ArmyParameter EarthParam[3]; // To Be Sorted In Constructor [0] is max percentage
	ArmyParameter AlienParam[3]; // To Be Sorted In Constructor
	int A_Health_Range[2];
	int A_Capacity_Range[2];
	int A_Power_Range[2];
	int E_Health_Range[2];
	int E_Capacity_Range[2];
	int E_Power_Range[2];
	Game* MainGame;

public:

	RandGen(Game* MainGame , 
	int n, int Prob, int ES_P , int AS_P , int ET_P , int EG_P, int AM_P, int AD_P ,
	int A_Health_Range[],
	int A_Capacity_Range[],
	int A_Power_Range[] ,
	int E_Health_Range[],
	int E_Capacity_Range[],
	int E_Power_Range[]
	);

	void InitializeParameters(int ES_P, int AS_P, int ET_P, int EG_P, int AM_P, int AD_P );
	bool GenerateUnits();
	bool Generate(UnitType type);

};

