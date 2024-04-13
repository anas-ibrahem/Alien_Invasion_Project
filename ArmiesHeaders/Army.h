#pragma once
#include "unit.h"
#include "../DS/ArrayStack.h"
#include "../DS/LinkedQueue.h"
#include "../DS/DoubleLinkedQueue.h"
#include "../DS/priQueue.h"
#include "../DS/DynamicArray.h"



class Army {



	public :
		virtual bool AddUnit(unit* unit) = 0;
		virtual void PrintAliveUnits() = 0 ;
		//virtual unit* PickUnit() = 0 ;




};