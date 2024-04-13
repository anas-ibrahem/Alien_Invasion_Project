#ifndef GAME_H_
#define GAME_H_

#include <fstream>
#include <string>
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include"../ArmiesHeaders/EarthArmy/EarthArmy.h"
#include "..\RandGen\RandGen.h"





class Game {


private :
	int N; // Number of units to be gerated each time step
	int TimeStep;
	LinkedQueue<unit*>* killedList;
	RandGen* Generator;
	AlienArmy* A_Army;
	EarthArmy* E_Army;
	char mode; // s for silent a for interactive

public :


	Game();
	int GetTS() const;
	int NextTS(); // Increase Time Step by 1 and return the new value of it
	GenParameters ReadFile();
	void PrintAllStats();
	void PrintKilledUnits();
	void PrintFights();
	bool GenerateUnits(); // return 1 if the generation is successful and 0 if not (Prob Control)
	bool AddUnit(unit* unit);
	void SetMode(char mode);
	bool AddToKilled(unit* U);
	void PrintAliveUnits();

	//bool WriteFile(); // To Be implemented


	~Game();

};



#endif