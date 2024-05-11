#include "..\..\ArmiesHeaders\EarthArmy\EarthArmy.h"

EarthArmy::EarthArmy()
{
	InfPercentage = 0;
	InfThersholdPercentage = 0;

	ES_Attacker_Infected = false;
}


bool EarthArmy::AddUnit(unit* unit, char InsertDir)
{
	switch (unit->GetType()) {
	case unit::ET:
		return Tanks.push(unit);
	case unit::ES:
		return Soldiers.enqueue(unit);
	case unit::EG:
		return Gunneries.enqueue(unit,unit->getPower()*unit->getHealth());
	case unit::EH:
		return Healers.push(unit);
	default:
		return false;
	}
}





void EarthArmy::PrintAliveUnits()
{
	cout << "\033[32m";
	cout << "=============== Earth Army Alive Units ===============" << endl << endl;
	cout << "Infection Percentage : " << InfPercentage << "%" << endl << endl;
	cout << Soldiers.getCount() << " ES: ";
	Soldiers.print();
	cout << endl << endl << Tanks.getCount() << " ET: ";
	Tanks.print();
	cout << endl << endl << Gunneries.getCount() << " EG: ";
	Gunneries.print();
	cout << endl << endl << Healers.getCount() << " EH: ";
	Healers.print();
	cout << endl << endl << "=============== Unit Maintenance Units ===============" << endl;
	cout << UML.getCount() << " UML: ";
	UML.print();
	cout <<"\033[0m" ;
}

bool EarthArmy::PrintFights()
{
	bool ES_Is_Attacked = !ES_Attacked.isEmpty();
	bool ET_Is_Attacked = !ET_Attacked.isEmpty();
	bool EG_Is_Attacked = !EG_Attacked.isEmpty();
	bool EH_Is_Attacked = !EH_Attacked.isEmpty();

	if (EH_Is_Attacked)
		PrintFight(unit::EH);

	if (ES_Is_Attacked)
		PrintFight(unit::ES);

	if (ET_Is_Attacked)
		PrintFight(unit::ET);

	if (EG_Is_Attacked)
		PrintFight(unit::EG);



	return (ES_Is_Attacked || ET_Is_Attacked || EG_Is_Attacked || EH_Is_Attacked );
}

void EarthArmy::PrintFight(unit::UnitType type) {


	switch (type) {
	
	case unit::ES :
		cout << "ES " << ES_AttackerID << (ES_Attacker_Infected ? "*" : "") << " Attacked "; 
		ES_Attacked.print();
		cout << "\n";
		ES_Attacked.clear();
		
		break;

	case unit::ET:
		cout << "ET " << ET_AttackerID << " Attacked ";

		ET_Attacked.print();
		cout << "\n";
		ET_Attacked.clear();
		break;


	case unit::EG:
		cout << "EG " << EG_AttackerID << " Attacked ";

		EG_Attacked.print();
		cout << "\n";
		EG_Attacked.clear();

		break;

	case unit::EH:
		cout << "EH " << EH_AttackerID << " Healed ";

		EH_Attacked.print();
		cout << "\n";
		EH_Attacked.clear();
	
	
	default :
		break;
	}

	return;

}

unit* EarthArmy::PickUnit(unit::UnitType type , char PickDir)
{
	unit* temp = nullptr ;
	int I; // Dummy integer

	switch (type) {
	case unit::ET:
		Tanks.pop(temp);
		break;
	case unit::ES:
		Soldiers.dequeue(temp);
		break;
	case unit::EG:
		Gunneries.dequeue(temp, I);
		break;
	case unit::EH:
		Healers.pop(temp);
		break;
	default:
		break;

	}


	return temp;
}

bool EarthArmy::AddtoUML(unit* unit)
{
	if (unit) 
	{
		switch (unit->GetType())
		{

		case unit::ES: 
			if (unit -> isInfected())
				eSoldier::ReduceInfectedCount(); // Assumption Count should discard the joining infected to UML
												 // As they Considered Dead or Immuned

			if (UML.enqueue(unit, INT_MAX / unit->getHealth())) // Adds Soldiers so that lowest health has largest Pri
				return true;
			break;

		case unit::ET:
			if (UML.enqueue(unit, -1))
				return true;
			break;

		default:
			break;
		}
	}
	return false;
}

unit* EarthArmy::PickfromUML()
{
	unit* temp = nullptr;
	int I; // Dummy integer
	UML.dequeue(temp, I);
	return temp;
}


void EarthArmy::attack()
{
	unit* Attacker = nullptr;

	if (Healers.pop(Attacker))
	{
		Attacker->attack(EH_Attacked);
		EH_AttackerID = Attacker->getID();
	}

	if (Soldiers.peek(Attacker))
	{
		ES_Attacker_Infected = Attacker->isInfected();

		Attacker->attack(ES_Attacked);
		ES_AttackerID = Attacker->getID();
	}

	if (Tanks.peek(Attacker))
	{
		Attacker->attack(ET_Attacked);
		ET_AttackerID = Attacker->getID();
	}

	int I; // Dummy Int 
	if (Gunneries.peek(Attacker , I))
	{
		Attacker->attack(EG_Attacked);
		EG_AttackerID = Attacker->getID();
	}


}


int EarthArmy::GetUnitCount(unit::UnitType type)
{


	switch (type)
	{

	case unit::ES:
		return Soldiers.getCount();
	case unit::EG:
		return Gunneries.getCount();
	case unit::ET:
		return Tanks.getCount();
	case unit::EH:
		return Healers.getCount();

	default:
		return 0;
	}
}

int EarthArmy::GetUMLCount()
{
	return UML.getCount();
}

void EarthArmy::CalcInfPercentage()
{
	if (Soldiers.getCount() == 0) InfPercentage = 0;
	else
	InfPercentage = eSoldier::getInfected_Count() * 100.0 / Soldiers.getCount();
}

double EarthArmy::GetInfPercentage() const
{
	return InfPercentage;
}

bool EarthArmy::CallAllied()
{
	return InfPercentage > InfThersholdPercentage;
}

void EarthArmy::SpreadInfection()
{
	int InfectionCount = eSoldier::getInfected_Count();

	for (; InfectionCount > 0; InfectionCount--) 
	{
		int ProbGen = rand() % 100 + 1;
		unit* tempES = nullptr;

		if (ProbGen <= 2) // 2% Prob of Spread for each soldier
		{
			LinkedQueue<unit*> templist;
			int RandESPick = rand() % Soldiers.getCount() + 1;
			
			while (Soldiers.dequeue(tempES))
			{
				if (RandESPick == 0)
				{
					if (!tempES->isInfected() && !tempES->isImmuned())
						tempES->setInfected(true);
					else
						RandESPick++; // Check Next One
				}

				templist.enqueue(tempES);
				RandESPick--;
			}

			while (templist.dequeue(tempES)) // Return units to Its Original List
				Soldiers.enqueue(tempES);
		}
	}
}

void EarthArmy::SetInfThershold(double perc)
{
	InfThersholdPercentage = perc;
}


EarthArmy::~EarthArmy()
{
}