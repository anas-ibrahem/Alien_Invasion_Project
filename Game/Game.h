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

	LinkedQueue<int>ESattack;
	LinkedQueue<int>ETattack;
	LinkedQueue<int>EGattack;

	LinkedQueue<int>ASattack;
	LinkedQueue<int>AMattack;
	LinkedQueue<int>ADattack;

public :

	



	Game();
	int GetTS() const;
	int NextTS(); // Increase Time Step by 1 and return the new value of it
	GenParameters ReadFile();
	void PrintAllStats();
	void PrintKilledUnits();
	bool GenerateUnits(); // return 1 if the generation is successful and 0 if not (Prob Control)
	bool AddUnit(unit* unit);
	void SetMode(char mode);
	bool AddToKilled(unit* U);
	void PrintAliveUnits();
	bool checkUML(unit* U);
	unit* PickUnit(unit::UnitType type , char dronedir = 'f');
	void  AddAttacked(unit::UnitType type, int id);

	



	void TestCode();



	// Phase 2 Added Functions 
	//bool WriteFile(); // To Be implemented
	void PrintFights();
	void Battle();

	~Game();

};



#endif