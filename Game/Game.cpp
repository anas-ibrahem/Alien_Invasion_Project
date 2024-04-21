#include "Game.h"
using namespace std;

Game::Game() {

	mode = 'a'; // default mode is 'a' // 's' for silent mode	// 'a' for interactive mode
	TimeStep = 1;
	A_Army = new AlienArmy();
	E_Army = new EarthArmy();
	killedList = new LinkedQueue<unit*>();
	Generator = new RandGen(ReadFile());
	srand(time(NULL)); // seed the random number generator // SEED ONCE NO NEED TO SEED AGAIN

}


void Game::SetMode(char mode)
{
	this->mode = mode;
}

bool Game::AddToKilled(unit*U)
{
	return killedList->enqueue(U);
}



int Game::GetTS() const
{
	return TimeStep;
}

int Game::NextTS()
{
	return ++TimeStep;
}



GenParameters Game::ReadFile()
{
	string inputfilename;
	cout << "Enter Input File Name : ex(input.txt)  * Make Sure the file is inside InputFiles Folder  " << endl;
	cin >> inputfilename;


	ifstream inFile("../InputFiles/" + inputfilename);
	while(!inFile.is_open()) // Re Ask If Name is Invalid
	{
		cout << "The Name you entered is invalid ... Enter a valid name" << endl;
		cin >> inputfilename;
		inFile.open("../InputFiles/"+ inputfilename);
	}
	GenParameters P;
	inFile >> N;

	inFile >> P.EarthPercentage[0] >> P.EarthPercentage[1] >> P.EarthPercentage[2] ;
	inFile >> P.AlienPercentage[0] >> P.AlienPercentage[1] >> P.AlienPercentage[2];


	inFile >> P.prob;
	inFile >> P.E_Power_Range[0];
	inFile >> P.E_Power_Range[1];
	P.E_Power_Range[1] *= -1;
	inFile >> P.E_Health_Range[0];
	inFile >> P.E_Health_Range[1];
	P.E_Health_Range[1] *= -1;
	inFile >> P.E_Capacity_Range[0];
	inFile >> P.E_Capacity_Range[1];
	P.E_Capacity_Range[1] *= -1;
	inFile >> P.A_Power_Range[0];
	inFile >> P.A_Power_Range[1];
	P.A_Power_Range[1] *= -1;
	inFile >> P.A_Health_Range[0];
	inFile >> P.A_Health_Range[1];
	P.A_Health_Range[1] *= -1;
	inFile >> P.A_Capacity_Range[0];
	inFile >> P.A_Capacity_Range[1];
	P.A_Capacity_Range[1] *= -1;
	inFile.close();

	return P;
}



bool Game::AddUnit(unit* unit)
{
	if ( unit->GetType() == unit::AD || unit->GetType() == unit::AS || unit->GetType() == unit::AM)
	{
		if (!A_Army->AddUnit(unit))// Delete the unit if it is not added to the army
		{
			delete unit;
			return false;
		}
	}
	else
	{
		if (!E_Army->AddUnit(unit)) // Delete the unit if it is not added to the army
		{
			delete unit;
			return false;
		}
	}
	return true;
}




void Game::PrintAliveUnits()
{

	E_Army->PrintAliveUnits();

	cout << "\n\n";

	A_Army->PrintAliveUnits();

}

unit* Game::PickUnit(unit::UnitType type , char dronedir)
{
	if (type == unit::AD || type == unit::AS || type == unit::AM)
	{
		return A_Army->PickUnit(type , dronedir);
	}
	else
	{
		return E_Army->PickUnit(type);

	}
}

void Game::AddAttacked(unit::UnitType type,int id)
{
	switch (type)
	{
	case unit::ES:
		ESattack.enqueue(id);
		break;
	case unit::ET:
		ETattack.enqueue(id);
		break;
	case unit::EG:
		EGattack.enqueue(id);
		break;
	case unit::AS:
		ASattack.enqueue(id);
		break;
	case unit::AM:
		AMattack.enqueue(id);
		break;
	case unit::AD:
		ADattack.enqueue(id);
		break;
	default:
		break;
	}
}



void Game::PrintKilledUnits()
{
	cout << "=============== Killed Units ===============" << endl;

	cout << killedList->getCount() << " units ";
	killedList->print();
}

void Game::PrintFights()
{
	cout << "=============== Fights  ===============" << endl;
	if (!ESattack.isEmpty()) {
		
		int id;
		cout << "ES"<< "  shots[";
		while (!ESattack.isEmpty()) {
			ESattack.dequeue(id);
			cout << id;
			if (!ESattack.isEmpty())
				cout << ", ";
		}
		cout << "] " << endl;
	}

	if (!ASattack.isEmpty()) {

		int id;
		cout << "AS" << "  shots[";
		while (!ASattack.isEmpty()) {
			ASattack.dequeue(id);
			cout << id;
			if (!ASattack.isEmpty())
				cout << ", ";
		}
		cout << "] " << endl;
	}

	cout << "\n\n";
}

void Game::Battle()
{
	E_Army->attack();
	A_Army->attack();

}

bool Game::GenerateUnits()
{
	if (!Generator->WillGenerate()) return false; // if didn't meet the prob


	for (int i = N; i > 0; --i) // Generate if meet the prob 
	{
		AddUnit(Generator->GenerateUnitEarth(TimeStep,this));
		AddUnit(Generator->GenerateUnitAlien(TimeStep,this));

	}


	return true;
}

void Game::PrintAllStats()
{
	cout << "Current TimeStep " << TimeStep << endl << endl;
	PrintAliveUnits();
	PrintFights();
	PrintKilledUnits();

}

void Game::TestCode()
{


	int X = rand() % 100 + 1;

	cout << "Current X  :  " << X << endl;


	if (X <= 10) {
		unit* ESDummy = PickUnit(unit::ES);
		if (ESDummy) AddUnit(ESDummy);
	}  
	else if (X <= 20) {
		unit* ETdummy = PickUnit(unit::ET);
		if (ETdummy) AddToKilled(ETdummy);
	}
	else if (X <= 30) {
		unit* EGdummy = PickUnit(unit::EG);

		if (EGdummy) {
			if (EGdummy->reduceHealth(EGdummy->getHealth() / 2)) // Really Won't Happen
				AddToKilled(EGdummy);

			AddUnit(EGdummy);
		}


	}
	else if (X <= 40) {

		unit* ASdummy;
		LinkedQueue<unit*> templist;

		for (int i = 0; i < 5; i++)
		{
			ASdummy = PickUnit(unit::AS);
			if (ASdummy) {

				if (ASdummy->reduceHealth(ASdummy->getHealth() / 2))  // Really Won't Happen
					AddToKilled(ASdummy);

				templist.enqueue(ASdummy);
			}
		}

		while (templist.dequeue(ASdummy))
			AddUnit(ASdummy);


	
	}
	else if (X <= 50) {
	
		unit* AMdummy;

		for (int i = 0; i < 5; i++)
		{
			AMdummy = PickUnit(unit::AM);

			if (AMdummy)
				AddUnit(AMdummy);

		}
	
	
	}
	else if (X <= 60) {
	
	
		unit* ADdummyF;
		unit* ADdummyR;


		for (int i = 0; i < 3; i++)
		{
			ADdummyF = PickUnit(unit::AD , 'f' );
			ADdummyR = PickUnit(unit::AD , 'r');
			if (ADdummyF) AddToKilled(ADdummyF);
			if (ADdummyR) AddToKilled(ADdummyR);

		}
	
	}

}

Game::~Game()
{
		cout << "\nClosing Game...........\n";
		cout << "\nDelete All Earth Army Units.............";
		delete E_Army;
		cout << "\nDelete All Alien Army Units.............";
		delete A_Army;
		cout << "\nDelete All Dead Units.............";
		delete killedList;

		// Deleting Generator
		delete Generator;
}
