#include"RandGen.h"

int GenerateValue(int Range[2]) {

	return ( rand() % (Range[1] - Range[0] + 1) + Range[0] );

}






RandGen::RandGen(Game* MainGame, int n, int Prob, int ES_P, int AS_P, int ET_P,
	int EG_P, int AM_P, int AD_P, int A_Health_Range[], int A_Capacity_Range[],
	int A_Power_Range[], int E_Health_Range[], int E_Capacity_Range[], int E_Power_Range[]) : MainGame(MainGame)
	, n(n) , Prob(Prob)
{
	InitializeParameters
		(ES_P, AS_P, ET_P, EG_P, AM_P, AD_P);
	srand(time(0));


	//MainGame->ReadFile("Input.txt");
	
}

void RandGen::InitializeParameters(int ES_P, int AS_P, int ET_P, int EG_P, int AM_P, int AD_P)
{
	//Sorting Percentage
	int MAX = max(ES_P, EG_P);
	MAX = max(MAX, ET_P);

	if (MAX == ES_P) {
		EarthParam[0].type = ES; EarthParam[0].Percentage = ES_P;
		MAX = max(EG_P, ET_P);
		if (MAX == EG_P) {
			EarthParam[1].type = EG; EarthParam[1].Percentage = EG_P;
			EarthParam[2].type = ET; EarthParam[2].Percentage = ET_P;
		}
		else {
			EarthParam[1].type = ET; EarthParam[1].Percentage = ET_P;
			EarthParam[2].type = EG; EarthParam[2].Percentage = EG_P;
		}
	}
	else if (MAX == EG_P) {
		EarthParam[0].type = EG; EarthParam[0].Percentage = EG_P;
		MAX = max(ES_P, ET_P);
		if (MAX == ES_P) {
			EarthParam[1].type = ES; EarthParam[1].Percentage = ES_P;
			EarthParam[2].type = ET; EarthParam[2].Percentage = ET_P;
		}
		else {
			EarthParam[1].type = ET; EarthParam[1].Percentage = ET_P;
			EarthParam[2].type = ES; EarthParam[2].Percentage = ES_P;
		}

	}
	else {
		EarthParam[0].type = ET; EarthParam[0].Percentage = ET_P;
		MAX = max(ES_P, EG_P);
		if (MAX == ES_P) {
			EarthParam[1].type = ES; EarthParam[1].Percentage = ES_P;
			EarthParam[2].type = EG; EarthParam[2].Percentage = EG_P;
		}
		else {
			EarthParam[1].type = EG; EarthParam[1].Percentage = EG_P;
			EarthParam[2].type = ES; EarthParam[2].Percentage = ES_P;
		}
	}

	MAX = max(AS_P, AM_P);
	MAX = max(MAX, AD_P);
	if (MAX == AS_P) {
		AlienParam[0].type = AS; AlienParam[0].Percentage = AS_P;
		MAX = max(AM_P, AD_P);
		if (MAX == AM_P) {
			AlienParam[1].type = AM; AlienParam[1].Percentage = AM_P;
			AlienParam[2].type = AD; AlienParam[2].Percentage = AD_P;
		}
		else {
			AlienParam[1].type = AD; AlienParam[1].Percentage = AD_P;
			AlienParam[2].type = AM; AlienParam[2].Percentage = AM_P;
		}
	}
	else if (MAX == AM_P) {
		AlienParam[0].type = AM; AlienParam[0].Percentage = AM_P;
		MAX = max(AS_P, AD_P);
		if (MAX == AS_P) {
			AlienParam[1].type = AS; AlienParam[1].Percentage = AS_P;
			AlienParam[2].type = AD; AlienParam[2].Percentage = AD_P;
		}
		else {
			AlienParam[1].type = AD; AlienParam[1].Percentage = AD_P;
			AlienParam[2].type = AS; AlienParam[2].Percentage = AS_P;
		}

	}
	else {
		AlienParam[0].type = AD; AlienParam[0].Percentage = AD_P;
		MAX = max(AS_P, AM_P);
		if (MAX == AS_P) {
			AlienParam[1].type = AS; AlienParam[1].Percentage = AS_P;
			AlienParam[2].type = AM; AlienParam[2].Percentage = AM_P;
		}
		else {
			AlienParam[1].type = AM; AlienParam[1].Percentage = AM_P;
			AlienParam[2].type = AS; AlienParam[2].Percentage = AS_P;
		}
	}
}

bool RandGen::GenerateUnits()
{
	int ProbGen = rand() % 100 + 1;
	if (ProbGen <= Prob) {

		for (int i = 0; i < n; ++i) {

			int ArmyGen = rand() % 100 + 1;
			if (ArmyGen <= EarthParam[0].Percentage )
				Generate(EarthParam[0].type);
			else if (ArmyGen <= EarthParam[0].Percentage + EarthParam[1].Percentage)
				Generate(EarthParam[1].type);
			else 
				Generate(EarthParam[2].type);

		}


		for (int i = 0; i < n; ++i) {

			int ArmyGen = rand() % 100 + 1;
			if (ArmyGen <= AlienParam[0].Percentage)
				Generate(AlienParam[0].type);
			else if (ArmyGen <= AlienParam[0].Percentage + AlienParam[1].Percentage)
				Generate(AlienParam[1].type);
			else
				Generate(AlienParam[2].type);

		}


		return true; // Yes Generated
		MainGame->IncreaseTime(1); //Increase Game Time By 1 // To be moved to Game.cpp

	}
		return false;// NO Generated
		MainGame->IncreaseTime(1); //Increase Game Time By 1/  To be moved to Game.cpp

}



bool RandGen::Generate(UnitType type)
{
	switch (type) {

	case AD: {
		aDrone* D = new aDrone(MainGame->GetTime(), GenerateValue(A_Health_Range), 
								GenerateValue(A_Capacity_Range) , GenerateValue(A_Power_Range) );
		MainGame->AddUnit(D);
		break;

	}
	case AS:

	{
		aSolider* S = new aSolider(MainGame->GetTime(), GenerateValue(A_Health_Range),
						GenerateValue(A_Capacity_Range), GenerateValue(A_Power_Range));
		MainGame->AddUnit(S);
		break;
	}
	case AM:
	{
		aMonster* M = new aMonster(MainGame->GetTime(), GenerateValue(A_Health_Range),
									GenerateValue(A_Capacity_Range), GenerateValue(A_Power_Range));
		MainGame->AddUnit(M);
		break;
	}
	//case ES:
	//{
	//	eSolider* S = new eSolider(MainGame->GetTime(), GenerateValue(E_Health_Range),
	//											GenerateValue(E_Capacity_Range), GenerateValue(E_Power_Range));
	//	MainGame->AddUnit(S);
	//	break;
	//}
	//case ET:
	//{
	//	eTank* T = new eTank(MainGame->GetTime(), GenerateValue(E_Health_Range),
	//										GenerateValue(E_Capacity_Range), GenerateValue(E_Power_Range));
	//	MainGame->AddUnit(T);
	//	break;
	//}
	//case EG:
	//{
	//	eGunnery* G = new eGunnery(MainGame->GetTime(), GenerateValue(E_Health_Range),
	//													GenerateValue(E_Capacity_Range), GenerateValue(E_Power_Range));
	//	MainGame->AddUnit(G);
	//	break;
	//}

	default:
		break;
	}

	return true;
}

