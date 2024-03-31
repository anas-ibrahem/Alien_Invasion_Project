#pragma once
#include <iostream>
using namespace std;

class unit
{
		int id;
		std::string type;
		int Tj;
		int Ta;
		int Health;
		int AttackCapacity;
		//RandGen* RG = new RandGen;
public:
	unit(int id , string type , int Tj , int Ta , int Health , int AttackCapacity);
	virtual bool attack() = 0;
	virtual bool defend() = 0;
	virtual bool isDead(); // Implementes As it's the same for all

};

