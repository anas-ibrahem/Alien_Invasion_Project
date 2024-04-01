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
	
}
