#include "Game.h"
using namespace std;

Game::Game() {

	mode = 'a'; // default mode is 'a' // 's' for silent mode	// 'a' for interactive mode
	TimeStep = 1;
	Generator = new RandGen(ReadFile());
	srand(time(NULL)); // seed the random number generator

}


void Game::SetMode(char mode)
{
	this->mode = mode;
}



int Game::GetTS() const
{
	return TimeStep;
}

int Game::NextTS()
{
	return ++TimeStep;
}



GenParameters Game::ReadFile()
{
	// TODO : Reask The file name if it is not found
	string input;
	cout << "Enter Input File Name : ex(input.txt)" << endl;
	cin >> input;


	ifstream inFile(input);
	GenParameters P;
	inFile >> N;
	cin.ignore(256, '\n'); // Clear the buffer

	//UnitTypePercentage temp;
	string Range;
	//P.Earth[0].type = ES;		P.Earth[1].type = ET;		P.Earth[2].type = EG;
	//P.Alien[0].type = AS;		P.Alien[1].type = AM;		P.Alien[2].type = AD;
	inFile >> P.EarthPercentage[0] >> P.EarthPercentage[1] >> P.EarthPercentage[2] ;
	inFile >> P.AlienPercentage[0] >> P.AlienPercentage[1] >> P.AlienPercentage[2];


	//for (int i = 0; i < 2; i++)
	//	for (int j = 0; j < 2 - i; j++)				//bubble sort
	//	{
	//		if (P.Earth[j].Percentage < P.Earth[j + 1].Percentage)
	//		{
	//			temp = P.Earth[j];
	//			P.Earth[j] = P.Earth[j + 1];
	//			P.Earth[j + 1] = temp;
	//		}
	//		if (P.Alien[j].Percentage < P.Alien[j + 1].Percentage)
	//		{
	//			temp = P.Alien[j];
	//			P.Alien[j] = P.Alien[j + 1];
	//			P.Alien[j + 1] = temp;
	//		}
	//	}



	inFile >> P.prob;
	inFile >> Range;
	FixRanges(Range, P.E_Power_Range);
	inFile >> Range;
	FixRanges(Range, P.E_Health_Range);
	inFile >> Range;
	FixRanges(Range, P.E_Capacity_Range);
	inFile >> Range;
	FixRanges(Range, P.A_Power_Range);
	inFile >> Range;
	FixRanges(Range, P.A_Health_Range);
	inFile >> Range;
	FixRanges(Range, P.A_Capacity_Range);


	return P;
}



bool Game::AddUnit(unit* unit)
{
	if ( unit->GetType() == AD || unit->GetType() == AS || unit->GetType() == AM)
	{
		if (!A_Army.AddUnit(unit))// Delete the unit if it is not added to the army
		{
			delete unit;
			return false;
		}
	}
	else
	{
		if (!E_Army.AddUnit(unit)) // Delete the unit if it is not added to the army
		{
			delete unit;
			return false;
		}
	}
	return true;
}



void Game::FixRanges(string input, int array[])
{
	string nums1 = "", nums2 = "";
	int i = 0;
	while (input[i] != '-')
	{
		nums1 += input[i];
		i++;
	}
	for (++i; i < input.length(); i++)
	{
		nums2 += input[i];
	}
	array[0] = stoi(nums1);
	array[1] = stoi(nums2);
}


void Game::PrintAliveUnits()
{

	E_Army.PrintAliveUnits();

	cout << "\n\n";

	A_Army.PrintAliveUnits();

}

void Game::PrintKilledUnits()
{
}

void Game::PrintFights()
{
}

bool Game::GenerateUnits()
{
	if (!Generator->WillGenerate()) return false; // if didn't meet the prob


	for (int i = N; i > 0; --i) // Generate if meet the prob 
	{
		AddUnit(Generator->GenerateUnitEarth(TimeStep));
		AddUnit(Generator->GenerateUnitAlien(TimeStep));

	}


	return true;
}



void Game::PrintAllStats()
{
	cout << "Current TimeStep " << TimeStep << endl << endl;
	PrintAliveUnits();
	PrintFights();
	PrintKilledUnits();

}


Game::~Game()
{
	delete Generator;
}

