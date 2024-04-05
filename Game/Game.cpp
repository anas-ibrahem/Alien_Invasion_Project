#include "Game.h"

using namespace std;


Game::Game() {

	TimeStep = 1;

}

int Game::GetTime() const
{
	return TimeStep;
}

bool Game::IncreaseTime(int Duration)
{
	TimeStep += Duration;
	return true;
}

bool Game::ReadFile(int& n, int& prob, ArmyParameter* Earth, ArmyParameter* Alien,
	int*A_Health_Range,
	int*A_Capacity_Range,
	int*A_Power_Range,
	int*E_Health_Range,
	int*E_Capacity_Range,
	int*E_Power_Range)
{
	ifstream inFile("input");
	inFile >> n;
	ArmyParameter temp;
	string Range;
	Earth[0].type = ES;		Earth[1].type = ET;		Earth[2].type = EG;
	Alien[0].type = AS;		Alien[1].type = AM;		Alien[2].type = AD;
	inFile >> Earth[0].Percentage >> Earth[1].Percentage >> Earth[2].Percentage;
	inFile >> Alien[0].Percentage >> Alien[1].Percentage >> Alien[2].Percentage;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2 - i; j++)				//bubble sort
		{
			if (Earth[j].Percentage < Earth[j + 1].Percentage)
			{
				temp = Earth[j];
				Earth[j] = Earth[j + 1];
				Earth[j + 1] = temp;
			}
			if (Alien[j].Percentage < Alien[j + 1].Percentage)
			{
				temp = Alien[j];
				Alien[j] = Alien[j + 1];
				Alien[j + 1] = temp;
			}
		}
	inFile >> prob;
	inFile >> Range;
	FixRanges(Range, E_Power_Range);
	inFile >> Range;
	FixRanges(Range, E_Health_Range);
	inFile >> Range;
	FixRanges(Range, E_Capacity_Range);
	inFile >> Range;
	FixRanges(Range, A_Power_Range);
	inFile >> Range;
	FixRanges(Range, A_Health_Range);
	inFile >> Range;
	FixRanges(Range, A_Capacity_Range);
	return true;
}



bool Game::AddUnit(unit* unit)
{
	if ( (unit->GetType() == AD || unit->GetType() == AS ) || unit->GetType() == AM )
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

void Game::FixRanges(string input, int*array)
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



Game::~Game()
{
}