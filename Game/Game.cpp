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

void Game::PrintAliveUnits()
{

	E_Army.PrintAliveUnits();
	cout << "\n\n";

	A_Army.PrintAliveUnits();
	
}



Game::~Game()
{
}