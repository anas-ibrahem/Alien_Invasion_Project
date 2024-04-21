#include "RandGen.h"

RandGen::RandGen(GenParameters P) : Data(P)
{
	LastAlienID = 2000;
	LastEarthID = 1;


}



bool RandGen::WillGenerate() const
{
	int ProbGen = rand() % 100 + 1;
	return (ProbGen <= Data.prob);

}

unit* RandGen::GenerateUnitAlien(int TimeJoin, Game* game)
{

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.AlienPercentage[0])
		return Create(unit::AS,  TimeJoin,game);
	else if (ArmyGen <= Data.AlienPercentage[0] + Data.AlienPercentage[1])
		return Create(unit::AM, TimeJoin,game);
	else
		return Create(unit::AD, TimeJoin,game);


}


unit* RandGen::GenerateUnitEarth(int TimeJoin, Game* game)
{

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.EarthPercentage[0])
		return Create(unit::ES, TimeJoin,  game);
	else if (ArmyGen <= Data.EarthPercentage[0] + Data.EarthPercentage[1])
		return Create(unit::ET, TimeJoin,game);
	else
		return Create(unit::EG, TimeJoin,game);
}

int RandGen::ValueRand(int Range[])
{
	return (rand() % (Range[1] - Range[0] + 1) + Range[0]);
}

unit* RandGen::Create(unit::UnitType T , int TimeJoin, Game* game)
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
	default :
		return nullptr;

	}

}
