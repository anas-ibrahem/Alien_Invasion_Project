#pragma once
#include "../DS/ArrayStack.h"
#include "../DS/LinkedQueue.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/priQueue.h"
#include "../DS/DynamicArray.h"


class unit;

class Army {



	public :

		virtual bool AddUnit(unit* unit, char InsertDir = 'n') = 0; // n for nonsent f for front r for rear
		virtual void PrintAliveUnits() = 0 ;
		virtual bool PrintFights() = 0;
		virtual void PrintFight(unit::UnitType type) = 0;
		virtual unit* PickUnit(unit::UnitType type , char PickDir = 'n') = 0 ; // n for nonsent f for front r for rear
		virtual void attack() = 0;


};