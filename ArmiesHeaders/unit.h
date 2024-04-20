#pragma once
#include <iostream>
using namespace std;

class Game;

class unit
{
public:


	enum UnitType {
		ES = 1,
		AS = 2,
		ET = 3,
		EG = 4,
		AM = 5,
		AD = 6,
		EH = 7
	};
	unit(int id , UnitType type , int Tj  , double Health , int AttackCapacity , int AttackPower,Game*game);
	virtual bool attack() = 0;
	virtual bool getAttacked(unit* Attacker);
	virtual bool isDead() const; // Implementes As it's the same for all
	double getHealth() const;
	int getPower() const;
	int getID() const;
	bool reduceHealth(int amount); // returns true if the unit died
	UnitType GetType() const;



protected:



		int id;
		UnitType type;
		int Tj;
		int Ta;
		int Td;
		double Health;
		int AttackCapacity;
		int AttackPower;
		Game* game;




};

