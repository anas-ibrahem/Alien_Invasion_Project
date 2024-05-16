#include "RandGen.h"

RandGen::RandGen(GenParameters P) : Data(P)
{
	// 1 -> 999
	// 2000 -> 2999
	// 4000 -> 4249

	LastEarthID = 1; // Initial IDS for Each
	LastAlienID = 2000;
	LastAlliedID = 4000;

}



bool RandGen::WillGenerate() const
{
	int ProbGen = rand() % 100 + 1; // Helper Function To Check Prob
	return (ProbGen <= Data.prob);

}

unit* RandGen::GenerateUnitAlien(int TimeJoin, Game* game)
{
	if (LastAlienID == 3000) return nullptr; // OUT of IDS


	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.AlienPercentage[0])
		return Create(unit::AS,  TimeJoin,game);
	else if (ArmyGen <= Data.AlienPercentage[0] + Data.AlienPercentage[1])
		return Create(unit::AM, TimeJoin,game);
	else
		return Create(unit::AD, TimeJoin,game);


	return nullptr;
}


unit* RandGen::GenerateUnitEarth(int TimeJoin, Game* game)
{

	if (LastEarthID == 1000) return nullptr; // OUT of IDS

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.EarthPercentage[0])
		return Create(unit::ES, TimeJoin,  game);
	else if (ArmyGen <= Data.EarthPercentage[0] + Data.EarthPercentage[1])
		return Create(unit::ET, TimeJoin,game);
	else if (ArmyGen <= Data.EarthPercentage[0] + Data.EarthPercentage[1] + Data.EarthPercentage[2] )
		return Create(unit::EG, TimeJoin,game);
	else 
		return Create(unit::EH, TimeJoin, game);

	
	return nullptr;
}

unit* RandGen::GenerateUnitAllied(int TimeJoin, Game* game)
{

	if (LastAlliedID == 4250) return nullptr; // OUT of IDS

	return Create(unit::SU, TimeJoin, game);

}

int RandGen::ValueRand(int Range[])
{
	return (rand() % (Range[1] - Range[0] + 1) + Range[0]);
}



unit* RandGen::Create(unit::UnitType T, int TimeJoin, Game* game)
{

	switch (T) {

	case unit::AD: {
		return new aDrone(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) , game);

	}
	case unit::AS:

	{
	return new aSoldier(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) , game);

	}
	case unit::AM:
	{
	return new aMonster(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range), game);

	}
	case unit::ES:
	{
	return new eSoldier(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) , game);
	}
	case unit::ET:
	{
	return new eTank(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range), game);

	}
	case unit::EG:
	{
	return new eGunnery(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) , game);

	}
	case unit::EH:
	{
		return new eHeal(LastEarthID++, TimeJoin, ValueRand(Data.E_Health_Range),
			ValueRand(Data.E_Capacity_Range), ValueRand(Data.E_Power_Range), game);

	}

	case unit::SU:
	{
		return new alSaver(LastAlliedID++, TimeJoin, ValueRand(Data.AL_Health_Range),
			ValueRand(Data.AL_Capacity_Range), ValueRand(Data.AL_Power_Range), game); 

	}

	default :
		return nullptr;

	}

}


RandGen::~RandGen()
{
}