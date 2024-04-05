#pragma once
#include <fstream>
#include <string>
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include"../ArmiesHeaders/EarthArmy/EarthArmy.h"
//#include "..\RandGen\RandGen.h"
#include "../DS/LinkedQueue.h"
#include"../DS/ArrayStack.h"
#include"../DS/priQueue.h"

class Game {
private:
	int TimeStep;
	LinkedQueue<unit*> killedList;
	AlienArmy A_Army;
	EarthArmy E_Army;
	
public :
	Game();
	int GetTime() const;
	bool IncreaseTime(int Duration);
	bool ReadFile(int& n, int& prob,
		ArmyParameter*Earth,
		ArmyParameter*Alien,
		int*A_Health_Range,
		int*A_Capacity_Range,
		int*A_Power_Range,
		int*E_Health_Range,
		int*E_Capacity_Range,
		int*E_Power_Range);
	bool WriteFile(); // To Be implemented
	bool AddUnit(unit* unit);
	void FixRanges(string input, int*array);
	void PrintAliveUnits();
	~Game();
};