#pragma once
#include "unit.h"

class Army {



	public :
		virtual bool AddUnit(unit* unit) = 0;
		virtual void PrintAliveUnits() = 0 ;
		//virtual unit* PickUnit() = 0 ;




};