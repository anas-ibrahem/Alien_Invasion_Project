#include "RandGen.h"

RandGen::RandGen(GenParameters P) : Data(P)
{
	LastAlienID = 2000;
	LastEarthID = 1;


}



bool RandGen::WillGenerate()
{
	int ProbGen = rand() % 100 + 1;
	return (ProbGen <= Data.prob);

}

unit* RandGen::GenerateUnitAlien(int TimeJoin)
{

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.AlienPercentage[0])
		return Create(unit::AS,  TimeJoin);
	else if (ArmyGen <= Data.AlienPercentage[0] + Data.AlienPercentage[1])
		return Create(unit::AM, TimeJoin);
	else
		return Create(unit::AD, TimeJoin);


}


unit* RandGen::GenerateUnitEarth(int TimeJoin)
{

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.EarthPercentage[0])
		return Create(unit::ES, TimeJoin);
	else if (ArmyGen <= Data.EarthPercentage[0] + Data.EarthPercentage[1])
		return Create(unit::ET, TimeJoin);
	else
		return Create(unit::EG, TimeJoin);
}

int RandGen::ValueRand(int Range[])
{
	return (rand() % (Range[1] - Range[0] + 1) + Range[0]);
}

unit* RandGen::Create(unit::UnitType T , int TimeJoin)
{

	switch (T) {

	case unit::AD: {
		return new aDrone(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case unit::AS:

	{
	return new aSoldier(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case unit::AM:
	{
	return new aMonster(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case unit::ES:
	{
	return new eSoldier(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );
	}
	case unit::ET:
	{
	return new eTank(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );

	}
	case unit::EG:
	{
	return new eGunnery(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );

	}

	}

}
