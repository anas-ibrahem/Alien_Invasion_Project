#pragma once
#include "../DS/ArrayStack.h"
#include "../DS/LinkedQueue.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/priQueue.h"
#include "../DS/DynamicArray.h"


class unit;

class Army {



	public :
		virtual bool AddUnit(unit* unit) = 0;
		virtual void PrintAliveUnits() = 0 ;
		virtual unit* PickUnit(unit::UnitType type , char dronedir = 'f') = 0 ;
		virtual void attack() = 0;


};