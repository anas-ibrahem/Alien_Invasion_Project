#ifndef GAME_H_
#define GAME_H_

#include <fstream>
#include <string>
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include"../ArmiesHeaders/EarthArmy/EarthArmy.h"
#include "..\RandGen\RandGen.h"
#include <conio.h>




class Game {


private :
	int N; // Number of units to be gerated each time step
	int TimeStep;
	LinkedQueue<unit*>* killedList;
	RandGen* Generator;
	AlienArmy* A_Army;
	EarthArmy* E_Army;
	char mode; // s for silent a for interactive
	char winner; // a for alien e for earth t for tie

	// Current Attack Lists

public :

	



	Game();
	int GetTS() const;
	int NextTS(); // Increase Time Step by 1 and return the new value of it
	GenParameters ReadFile();
	void PrintAllStats();
	void PrintKilledUnits();
	void GenerateUnits(); 
	bool AddUnit(unit* unit , char InsertDir = 'n'); // n for nonsent f for front r for rear
	void SetMode(char mode);
	bool AddToKilled(unit* U);
	void PrintAliveUnits();
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear
	int GetUnitCount(unit::UnitType type);


	



	void TestCode();



	// Phase 2 Added Functions 
	void WriteFile(); // To Be implemented
	void PrintFights();
	void Battle();
	bool AddUML(unit* U);
	unit* PickUML();
	void StartMenu();
	void Simulate(); // Main Game Loop
	char WL_Check(); // Win Lose Check Function Return e for Earth Winner , a for Alien , t for tie , n for none
	void Print_ASCII_ART();


	~Game();

};



#endif