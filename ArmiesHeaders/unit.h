#pragma once
#include <iostream>

using namespace std;
class Game;

template<typename Type>
class LinkedQueue;


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


	unit(int id , UnitType type , int Tj  , double Health , int AttackCapacity , double AttackPower, Game*game);
	virtual bool attack(LinkedQueue<int>& AttackedIDs) = 0; // Just To avoid Abstract Error
	virtual bool getAttacked(unit* Attacker);
	virtual bool getHealed(unit* Attacker);
	virtual bool isDead() const; // Implementes As it's the same for all
	double getHealth() const;
	double HealthPercent() const;
	double getPower() const;
	int getID() const;
	bool reduceHealth(double amount); // returns true if the unit died
	UnitType GetType() const;
	void setTD(int T);
	int getTa() const;
	int getTd() const;
	void setTa(int T);

protected:
		int id;
		UnitType type;
		int Tj;
		int Ta;
		int Td;
		double Health;
		double intialHealth;
		int AttackCapacity;
		double AttackPower;
		Game* game;
};

