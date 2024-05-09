#include "..\..\ArmiesHeaders\AlliedArmy\AlliedArmy.h"

AlliedArmy::AlliedArmy()
{
}


bool AlliedArmy::AddUnit(unit* unit, char InsertDir)
{
	switch (unit->GetType()) {
	case unit::SU:
		return Savers.enqueue(unit);

	default:
		return false;
	}
}





void AlliedArmy::PrintAliveUnits()
{
	cout << "\033[32m";
	cout << "=============== Allied Army Alive Units ===============" << endl << endl;
	cout << Savers.getCount() << " SU: ";
	Savers.print();
	cout <<"\033[0m" ;
}

bool AlliedArmy::PrintFights()
{
	bool SU_Is_Attacked = !SU_Attacked.isEmpty();

	if (SU_Is_Attacked)
		PrintFight(unit::SU);


	return (SU_Is_Attacked);
}

void AlliedArmy::PrintFight(unit::UnitType type) {


	switch (type) {
	
	case unit::SU :
		cout << "SU " << SU_AttackerID << " Attacked ";
		SU_Attacked.print();
		cout << "\n";
		SU_Attacked.clear();
		
		break;
	
	default :
		break;
	}

	return;

}

unit* AlliedArmy::PickUnit(unit::UnitType type , char PickDir)
{
	unit* temp = nullptr ;

	switch (type) {
	case unit::SU :
		Savers.dequeue(temp);
		break;

	default:
		break;

	}


	return temp;
}




void AlliedArmy::attack()
{
	unit* Attacker = nullptr;

	if (Savers.peek(Attacker))
	{
		Attacker->attack(SU_Attacked);
		SU_AttackerID = Attacker->getID();
	}

}


int AlliedArmy::GetUnitCount(unit::UnitType type)
{


	switch (type)
	{
	case unit::SU:
		return Savers.getCount();

	default:
		return 0;
	}
}

void AlliedArmy::clearArmy()
{
	Savers.clear();
}



AlliedArmy::~AlliedArmy()
{
}