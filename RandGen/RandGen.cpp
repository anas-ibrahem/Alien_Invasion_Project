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
		return Create(AS,  TimeJoin);
	else if (ArmyGen <= Data.AlienPercentage[0] + Data.AlienPercentage[1])
		return Create(AM, TimeJoin);
	else
		return Create(AD, TimeJoin);


}


unit* RandGen::GenerateUnitEarth(int TimeJoin)
{

	int ArmyGen = rand() % 100 + 1;
	if (ArmyGen <= Data.EarthPercentage[0])
		return Create(ES, TimeJoin);
	else if (ArmyGen <= Data.EarthPercentage[0] + Data.EarthPercentage[1])
		return Create(ET, TimeJoin);
	else
		return Create(EG, TimeJoin);
}

int RandGen::ValueRand(int Range[])
{
	return (rand() % (Range[1] - Range[0] + 1) + Range[0]);
}

unit* RandGen::Create(UnitType T , int TimeJoin)
{

	switch (T) {

	case AD: {
		return new aDrone(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case AS:

	{
	return new aSoldier(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case AM:
	{
	return new aMonster(LastAlienID++ , TimeJoin , ValueRand(Data.A_Health_Range) ,
			ValueRand(Data.A_Capacity_Range) , ValueRand(Data.A_Power_Range) );

	}
	case ES:
	{
	return new eSoldier(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );
	}
	case ET:
	{
	return new eTank(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );

	}
	case EG:
	{
	return new eGunnery(LastEarthID++ , TimeJoin , ValueRand(Data.E_Health_Range) ,
			ValueRand(Data.E_Capacity_Range) , ValueRand(Data.E_Power_Range) );

	}

	}

}
