#pragma once
#include <iostream>
using namespace std;

enum UnitType {
	ES = 1,
	AS = 2,
	ET = 3,
	EG = 4,
	AM = 5,
	AD = 6
};


class unit
{
protected:
		int id;
		UnitType type;
		int Tj;
		int Ta;
		int Health;
		int AttackCapacity;
		int AttackPower;
		//RandGen* RG = new RandGen;
public:

	unit(int id , UnitType type , int Tj  , int Health , int AttackCapacity , int AttackPower);
	virtual bool attack() = 0;
	virtual bool defend() = 0;
	virtual bool isDead(); // Implementes As it's the same for all
	UnitType GetType() const;

};

