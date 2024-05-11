#pragma once
#include <iostream>

using namespace std;
class Game;

template<typename Type>
class LinkedQueue;


class unit
{
public:

	//Shared Members
	static int GetNumOfHealed();
	enum UnitType {
		ES = 1,
		AS = 2,
		ET = 3,
		EG = 4,
		AM = 5,
		AD = 6,
		EH = 7,
		SU = 8
	};
	


	unit(int id , UnitType type , int Tj  , double Health , int AttackCapacity , double AttackPower, Game*game);
	//Pure virtual 
	virtual bool attack(LinkedQueue<unit*>& AttackedUnits) = 0;

	//Shared Functions(Same for all units)
	bool getAttacked(unit* Attacker);
	bool getHealed(unit* Attacker);
	bool reduceHealth(double amount); // returns true if the unit died
	double HealthPercent() const;

	// Setters
	void setTD(int T);
	void setTa(int T);
	void setTj_UML(int T);


	
	// Getters
	double getPower() const;
	UnitType GetType() const;
	int getID() const;
	int getTa() const;
	int getTj() const;
	int getTd() const;
	int getTj_UML() const;
	double getHealth() const;

	// Flags
	bool isHealed() const;
	bool isDead() const; // Implementes As it's the same for all
	bool CanJoinUML() const;

	// Flags (Special for ES)
	virtual bool isInfected();
	virtual bool isImmuned();
	virtual void setInfected(bool Infect);
	virtual void setImmuned(bool Immune);

protected:
		//Shared Member (static)
		static int Num_Healed;
		
		//Members
		int id;
		UnitType type;

		int Tj;
		int Ta;
		int Td;
		int Tj_UML; // Time Joining UML

		double Health;
		double intialHealth;
		bool Healed;

		int AttackCapacity;
		double AttackPower;

		Game* game;
};

