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
		A_Army.AddUnit(unit);
	}
	else
	{
		//E_Army.AddUnit(unit);
	}
	return 1;
}

void Game::PrintAliveUnits()
{
	A_Army.PrintAliveUnits();
	//E_army 
}



Game::~Game()
{
}