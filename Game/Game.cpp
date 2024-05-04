#include "Game.h"
using namespace std;

Game::Game() {

	mode = 'a'; // default mode is 'a' // 's' for silent mode	// 'a' for interactive mode
	winner = 'n'; // none 
	TimeStep = 0;
	A_Army = new AlienArmy();
	E_Army = new EarthArmy();
	killedList = new LinkedQueue<unit*>();
	srand(time(NULL)); // seed the random number generator // SEED ONCE NO NEED TO SEED AGAIN
	StartMenu();

}

void Game::StartMenu()
{
	Print_ASCII_ART();

	Generator = new RandGen(ReadFile());
	cout << "\nEnter Game Mode 'a' for Interactive 's' for Silent\n";
	char c;
	cin >> c;

	while (c != 'a' && c != 's' && c != 'A' && c != 'S')
	{
		cout << "\nInvalid Input Enter a valid choice\n";
		cin >> c;
	}
	
	
	cout << "\n============== Simulation Starts ===============";
	if (c == 'a' || c == 'A')
	{
		mode = 'a';
		cout << "\nInteractive Mode Watch THE WAR !!!!\n";
	}
	else if (c == 's' || c == 'S') 
	{ 
		mode = 's'; 
		cout << "\n~~~~~~~~~Silent Mode  SHHHHHHHHHHHHHHHHH ! ~~~~~~~~~~~~~";

	}

}


void Game::Simulate()
{

	do {


		NextTS();
		GenerateUnits();
		Battle();
		if (mode == 'a')
		{
			cout << "\n\n";
			PrintAllStats();
			cout << "\n\nPress any key to continue" << endl;
			_getch(); // wait for user to press any key to continue
			cout << "\n\n\n\n";
		}

		if (TimeStep >= 40) // Wait at least 40 timesteps 
			winner = WL_Check();

	} while (winner == 'n');


	WriteFile();
	cout << "\n=============== Simulation END =================";


}

char Game::WL_Check()
{

	long int E_Total = GetUnitCount(unit::ET) + GetUnitCount(unit::ES) + GetUnitCount(unit::EG) + GetUnitCount(unit::EH);
	// Assume EH is Considered // As UML May change the Winner
	long int A_Total = GetUnitCount(unit::AD) + GetUnitCount(unit::AS) + GetUnitCount(unit::AM);

	// Tie Check
	// if both total = 0 or the Left units are not able to attack each other (following cases)
	// ES and AD only
	// EG and AS only
	int ESC = GetUnitCount(unit::ES);
	int EGC = GetUnitCount(unit::EG);
	int ASC = GetUnitCount(unit::AS);
	int ADC = GetUnitCount(unit::AD); // Leave these variables for debugging

	if ((GetUnitCount(unit::ES) == E_Total && GetUnitCount(unit::AD) == A_Total) ||
		(GetUnitCount(unit::EG) == E_Total && GetUnitCount(unit::AS) == A_Total)
		|| (E_Total == 0 && A_Total == 0)) 
		return 't';


	else if (E_Total > 0 && A_Total == 0) 
		return 'e';
	else if (A_Total > 0 && E_Total == 0) 
		return 'a';
	else 
		return 'n';

}

void Game::Print_ASCII_ART()
{
	std::cout << "============================SIMULATE OR SURRNEDER !!!===========================" << std::endl << std::endl;
	std::cout << "                                               .-'\"\"p 8o\"\"   `-." << std::endl;
	std::cout << "       .-\"\"\"\"\"-.       .-\"\"\"\"-.              .-'8888P'Y.`Y[ '      `-. " << std::endl;
	std::cout << "      /        \\      /        \\          ,' ,88888888888[\"        Y`. " << std::endl;
	std::cout << "     /_        _\\    /_        _\\        /   8888888888P            Y8\\" << std::endl;
	std::cout << "    // \\      / \\\\  // \\      / \\\\      /    Y8888888P'             ]88\\" << std::endl;
	std::cout << "    |\\__\\    /__/|  |\\__\\    /__/|     :     `Y88'   P              `888: " << std::endl;
	std::cout << "     \\    ||    /    \\    ||    /      :       Y8.oP '- >            Y88: " << std::endl;
	std::cout << "      \\        /      \\        /       |          `Yb  __             `'|" << std::endl;
	std::cout << "       \\  __  /        \\  __  /        :            `'d8888bo.          : " << std::endl;
	std::cout << "        '.__.'          '.__.'         :             d88888888ooo.      ; " << std::endl;
	std::cout << "         |  |            |  |          \\            Y88888888888P     / " << std::endl;
	std::cout << "         |  |            |  |           \\            `Y88888888P     / " << std::endl;
	std::cout << "                                          `.            d88888P'    ,'    " << std::endl;
	std::cout << "                                          `.          888PP'    ,'  " << std::endl;
	std::cout << "                                            `-.      d8P'    ,-'" << std::endl;
	std::cout << "                                               `-.,,_',_,.-' " << std::endl << std::endl;
	std::cout << "============================ALIEN INVASION SIMULATOR===========================" << std::endl;;
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

	inFile >> P.EarthPercentage[0] >> P.EarthPercentage[1] >> P.EarthPercentage[2] >>P.EarthPercentage[3];
	if (P.EarthPercentage[3] > 5) P.EarthPercentage[3] = 5;
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



bool Game::AddUnit(unit* unit, char InsertDir)
{
	if (!unit) return false; // Case Random Generator will send Null if Out Of IDS

	if ( unit->GetType() == unit::AD || unit->GetType() == unit::AS || unit->GetType() == unit::AM)
	{
		if (!A_Army->AddUnit(unit , InsertDir))// Delete the unit if it is not added to the army
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

bool Game::checkUML(unit* U)
{
	if (U->HealthPercent() < 20 && U->HealthPercent() > 0)
		if (E_Army->AddtoUML(U))
		{
			U->setTD(TimeStep);
			return true;
		}
	return false;
}

unit* Game::PickUnit(unit::UnitType type , char PickDir)
{
	// Will return Null From the PickUnit of The armies in case not found

	if (type == unit::AD || type == unit::AS || type == unit::AM)
		return A_Army->PickUnit(type , PickDir);
	else
		return E_Army->PickUnit(type);

}

int Game::GetUnitCount(unit::UnitType type)
{
	if (type == unit::AD || type == unit::AS || type == unit::AM)
		return A_Army->GetUnitCount(type);
	else
		return E_Army->GetUnitCount(type);
}

unit* Game::PickUML()
{
		return E_Army->PickfromUML();
}



void Game::PrintKilledUnits()
{
	cout << "\n=============== Killed Units ===============" << endl;

	cout << killedList->getCount() << " units ";
	killedList->print();
}

void Game::WriteFile()
{
	int N_ES = 0, N_ET = 0, N_EG = 0, N_EH = 0; //N for each type killed
	int N_AS = 0, N_AD = 0, N_AM = 0;
	ofstream OutFile("../OutputFiles/output.txt");
	OutFile << "Td  \tID  \tTj  \tDf  \tDd  \tDb" << endl;
	LinkedQueue<unit*> temp;
	unit* tem;
	while (killedList->dequeue(tem))
	{
		temp.enqueue(tem);

		int Td = tem->getTd();
		int Tj = tem->getTj();
		int Ta = tem->getTa();
		OutFile << Td << "   \t" << tem->getID() << "   \t" << Tj << "   \t" << Ta - Tj << "   \t" << Td - Ta << "   \t" << Td - Tj << endl;
		switch (tem->GetType())
		{
		case unit::ES:
			N_ES++;
			break;
		case unit::ET:
			N_ET++;
			break;
		case unit::EG:
			N_EG++;
			break;
		case unit::EH:
			N_EH++;
			break;
		case unit::AS:
			N_AS++;
			break;
		case unit::AD:
			N_AD++;
			break;
		case unit::AM:
			N_AM++;
			break;
		default:
			break;
		}
	}
	while (temp.dequeue(tem))
	{
		killedList->enqueue(tem);
	}
}

void Game::PrintFights()
{
	cout << "=============== BATTLE ROUND  ===============" << endl;
	bool EarthBattle = E_Army->PrintFights();
	bool ALienBattle = A_Army->PrintFights();

	if (! (EarthBattle || ALienBattle )) 
		cout <<"\n\n~~~~SILENCE~ NOTHING HAPPENED ! ~SILENCE~~~~\n\n\n";

}

void Game::Battle()
{
	E_Army->attack();
	A_Army->attack();

}

void Game::GenerateUnits()
{
	bool GenerateAlienUnits = Generator->WillGenerate();
	bool GenerateEarthUnits = Generator->WillGenerate();

	if (GenerateAlienUnits)
		for (int i = N; i > 0; --i) // Generate if meet the prob 
		{
			unit* Created = Generator->GenerateUnitAlien(TimeStep, this);
			if (!Created && mode == 'a')
			{
				cout << "---------------- Can't Generate Alien IDs OUT OF RANGE ----------------"; break;
			}
			
			AddUnit(Created);
		}

	if (GenerateEarthUnits)
		for (int i = N; i > 0; --i) // Generate if meet the prob 
		{
			unit* Created = Generator->GenerateUnitEarth(TimeStep, this);
			if (!Created && mode =='a')
			{
				cout << "---------------- Can't Generate Earth IDs OUT OF RANGE ----------------"; break;
			}

			AddUnit(Created);
		}
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
		if (ESDummy) {
			ESDummy->reduceHealth(ESDummy->getHealth() / 2);
			ESDummy->reduceHealth(ESDummy->getHealth() / 2);
			ESDummy->reduceHealth(ESDummy->getHealth() / 2);
			if (!checkUML(ESDummy))
				AddUnit(ESDummy);
		}
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
		cout << "\n\nClosing Game...........";
		cout << "\nDelete All Earth Army Units.............";
		delete E_Army;
		cout << "\nDelete All Alien Army Units.............";
		delete A_Army;
		cout << "\nDelete All Dead Units.............";
		delete killedList;

		// Deleting Generator
		delete Generator;
}
