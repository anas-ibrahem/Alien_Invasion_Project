#ifndef GAME_H_
#define GAME_H_

#include <fstream>
#include <string>
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"
#include"../ArmiesHeaders/EarthArmy/EarthArmy.h"
#include"../ArmiesHeaders/AlliedArmy/AlliedArmy.h"
#include "..\RandGen\RandGen.h"
#include <conio.h>




class Game {


private :

	//Main Members
	int TimeStep;
	char mode; // s for silent a for interactive
	char winner; // a for alien e for earth t for tie

	//Genereator
	int N; // Number of units to be gerated each time step
	RandGen* Generator;

	//Lists
	LinkedQueue<unit*>* killedList;
	AlienArmy* A_Army;
	EarthArmy* E_Army;
	AlliedArmy* AL_Army;

public :

	// Game Starter Functions
	Game();
	void StartMenu();

	// Getters
	int GetTS() const;
	char GetMode() const ;
	int GetUnitCount(unit::UnitType type) const;
	int NextTS(); // Increase Time Step by 1 and return the new value of it

	//Files
	GenParameters ReadFile();
	void WriteFile(); 

	//Print Funcitons
	void PrintAllStats();
	void PrintAliveUnits();
	void PrintKilledUnits();
	void PrintFights();
	void Print_ASCII_ART();

	//Simulation & Test
	void Simulate(); // Main Game Loop
	void GenerateUnits(); 
	char WL_Check(); // Win Lose Check Function Return e for Earth Winner , a for Alien , t for tie , n for none
	void Battle();
	void TestCode();

	//Setters
	void SetMode(char mode);


	//Lists Control
	bool AddUnit(unit* unit , char InsertDir = 'n'); // n for nonsent f for front r for rear
	bool AddtoUML(unit* U);
	bool AddToKilled(unit* U);
	unit* PickUnit(unit::UnitType type , char PickDir = 'n'); // n for nonsent f for front r for rear
	unit* PickfromUML();
	void ClearUML();
	void IncTotalInfectedEarth();

	~Game();

};



#endif