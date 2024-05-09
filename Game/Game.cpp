#include "Game.h"
using namespace std;

Game::Game() {

	mode = 'a'; // default mode is 'a' // 's' for silent mode	// 'a' for interactive mode
	winner = 'n'; // none 
	InfectProb = 20; // FOR TEST
	TimeStep = 0;
	A_Army = new AlienArmy();
	E_Army = new EarthArmy();
	AL_Army = new AlliedArmy();
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

	ClearUML(); // Clear UML and move it's units to KilledList
	WriteFile();
	cout << "\n=============== Simulation END =================";


}

char Game::WL_Check()
{
	int UML_C = E_Army->GetUMLCount();
	int EH_C = GetUnitCount(unit::EH);
	long int E_Total = GetUnitCount(unit::ET) + GetUnitCount(unit::ES) + GetUnitCount(unit::EG) + EH_C + UML_C;
	long int A_Total = GetUnitCount(unit::AD) + GetUnitCount(unit::AS) + GetUnitCount(unit::AM);


	if (E_Total > 0 && A_Total == 0)
		return 'e';

	// Assume if only EH or if only UML then earth lost
	else if (A_Total > 0 && ( E_Total == 0 || E_Total == EH_C || E_Total == UML_C) )
		return 'a';

	// Tie Check
	// if both total = 0 or the Left units are not able to attack each other (following cases) ( Regardless of UML in case of no EH they are not considered )
	// ES and AD only
	// EG and AS only
	else if ((GetUnitCount(unit::ES) == E_Total - UML_C && GetUnitCount(unit::AD) == A_Total) ||
		(GetUnitCount(unit::EG) == E_Total - UML_C && GetUnitCount(unit::AS) == A_Total)
		|| (E_Total == 0 && A_Total == 0)) 

		return 't';
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

void Game::ClearUML()
{
	unit* temp = nullptr;
	while (temp = PickUML())
		AddToKilled(temp);
}

int Game::GetInfectProb() const
{
	return InfectProb;
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

	if (unit->GetType() == unit::SU) 
	{
		if (!AL_Army->AddUnit(unit, InsertDir))// Delete the unit if it is not added to the army
		{
			delete unit;
			return false;
		}
	
	}
	else if ( unit->GetType() == unit::AD || unit->GetType() == unit::AS || unit->GetType() == unit::AM)
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

	AL_Army->PrintAliveUnits();
	
	cout << "\n\n";

	A_Army->PrintAliveUnits();

}

bool Game::AddUML(unit* U)
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

char Game::getMode() const
{
	return mode;
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
	int N_ES_alive = 0, N_ET_alive = 0, N_EG_alive = 0, N_EH_alive = 0; //N for each type alive
	int N_AS = 0, N_AD = 0, N_AM = 0;
	int N_AS_alive = 0, N_AD_alive = 0, N_AM_alive = 0;
	double ESumDF = 0, ESumDD = 0, ESumDB = 0;
	double ASumDF = 0, ASumDD = 0, ASumDB = 0;
	double ASum_alive = 0, ASum_killed = 0, ASum_Total = 0;
	double ESum_alive = 0, ESum_killed = 0, ESum_Total = 0;

	ofstream OutFile("../OutputFiles/output.txt");


	OutFile << "////////////////// KILLED UNITS DATA /////////////////////\n";
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
			ESumDF += Ta - Tj;
			ESumDD += Td - Ta;
			ESumDB += Td - Tj;
			break;
		case unit::ET:
			N_ET++;
			ESumDF += Ta - Tj;
			ESumDD += Td - Ta;
			ESumDB += Td - Tj;
			break;
		case unit::EG:
			N_EG++;
			ESumDF += Ta - Tj;
			ESumDD += Td - Ta;
			ESumDB += Td - Tj;
			break;
		case unit::EH:
			N_EH++;
			ESumDF += Ta - Tj;
			ESumDD += Td - Ta;
			ESumDB += Td - Tj;
			break;
		case unit::AS:
			N_AS++;
			ASumDF += Ta - Tj;
			ASumDD += Td - Ta;
			ASumDB += Td - Tj;
			break;
		case unit::AD:
			N_AD++;
			ASumDF += Ta - Tj;
			ASumDD += Td - Ta;
			ASumDB += Td - Tj;
			break;
		case unit::AM:
			N_AM++;
			ASumDF += Ta - Tj;
			ASumDD += Td - Ta;
			ASumDB += Td - Tj;
			break;
		default:
			break;
		}
	}
	while (temp.dequeue(tem))
	{
		killedList->enqueue(tem);
	}
	N_ES_alive = E_Army->GetUnitCount(unit::ES);
	N_ET_alive = E_Army->GetUnitCount(unit::ET);
	N_EG_alive = E_Army->GetUnitCount(unit::EG);
	N_EH_alive = E_Army->GetUnitCount(unit::EH);
	N_AS_alive = A_Army->GetUnitCount(unit::AS);
	N_AM_alive = A_Army->GetUnitCount(unit::AM);
	N_AD_alive = A_Army->GetUnitCount(unit::AD);

	ESum_alive = N_ES_alive + N_ET_alive + N_EG_alive + N_EH_alive;
	ESum_killed = N_ES + N_ET + N_EG + N_EH;
	ESum_Total = ESum_alive + ESum_killed;

	ASum_alive = N_AS_alive + N_AD_alive + N_AM_alive;
	ASum_killed = N_AS + N_AD + N_AM;
	ASum_Total = ASum_alive + ASum_killed;

	switch (winner)
	{
	case 'a':
		OutFile << "      A   L   I   E   N    W   I   N   S\n";
		break;
	case 'e':
		OutFile << "      E   A   R   T   H    W   I   N   S\n";
		break;
	case 't':
		OutFile << "      D   R   A   W   /    T   I   E\n";
		break;
	case 'n':
		OutFile << "      N   O    B   O   D   Y    W   I   N   S\n";
		break;
	default:
		break;
	}

	OutFile << "////////////////// E A R T H  A R M Y /////////////////////\n";
	OutFile <<			   "ES: " << N_ES_alive + N_ES 
			<< "            ET: " << N_ET_alive + N_ET 
			<< "            EG: " << N_EG_alive + N_EG 
			<< "            EH: " << N_EH_alive + N_EH << endl;
	OutFile << "ES%: " << ((N_ES_alive + N_ES) ? (double)N_ES / (N_ES_alive + N_ES) * 100 : 0) << "%";
	OutFile << "            ET%: " << ((N_ET_alive + N_ET) ? (double)N_ET / (N_ET_alive + N_ET) * 100 : 0) << "%";
	OutFile << "            EG%: " << ((N_EG_alive + N_EG) ? (double)N_EG / (N_EG_alive + N_EG) * 100 : 0) << "%";
	OutFile << "            EH%: " << ((N_EH_alive + N_EH) ? (double)N_EH / (N_EH_alive + N_EH) * 100 : 0) << "%";
	OutFile << endl;
	OutFile << "Total Healed Percentage: " << ((ESum_Total) ? unit::NumOfHealed() * 100 / ESum_Total : 0) << "%";
	OutFile << endl;
	OutFile << "Total Destructed Percentage: " << ((ESum_Total) ? ESum_killed * 100 / ESum_Total : 0) << "%";
	OutFile << endl;
	if (ESum_killed) {
		OutFile <<    "Average of Df: " << ESumDF / ESum_killed 
				<< "\t ,Average of Dd: " << ESumDD / ESum_killed 
				<< "\t ,Average of Db: " << ESumDB / ESum_killed << endl;
		OutFile <<   "Df/Db% = " << ESumDF * 100 / ESumDB << "%"
				<< ", Dd/Db% = " << ESumDD * 100 / ESumDB << "%" << endl;
	}
	else
	{
		OutFile << "Average of Df: " << 0
			<< "\t ,Average of Dd: " << 0
			<< "\t ,Average of Db: " << 0 << endl;
		OutFile << "Df/Db% = " << 0 << "%"
			<< ", Dd/Db% = " << 0 << "%" << endl;
	}




	OutFile << "////////////////// A L I E N  A R M Y /////////////////////\n";
	OutFile <<			   "AS: " << N_AS_alive + N_AS
			<< "            AD: " << N_AD_alive + N_AD
			<< "            AM: " << N_AM_alive + N_AM << endl;
	OutFile << "AS%: " << ((N_AS_alive + N_AS) ? (double)N_AS / (N_AS_alive + N_AS) * 100 : 0) << "%";
	OutFile << "            AD%: " << ((N_AD_alive + N_AD) ? (double)N_AD / (N_AD_alive + N_AD) * 100 : 0) << "%";
	OutFile << "            AM%: " << ((N_AM_alive + N_AM) ? (double)N_AM / (N_AM_alive + N_AM) * 100 : 0) << "%";
	OutFile << endl;
	OutFile << "Total Destructed Percentage: " << ((ASum_Total) ? ASum_killed * 100 / ASum_Total : 0) << "%";
	OutFile << endl;
	if (ASum_killed) {
		OutFile << "Average of Df: " << ASumDF / ASum_killed
			<< "\t Average of Dd: " << ASumDD / ASum_killed
			<< "\t Average of Db: " << ASumDB / ASum_killed << endl;
		OutFile << "Df/Db% = " << ASumDF * 100 / ASumDB << "%"
			<< ", Dd/Db% = " << ASumDD * 100 / ASumDB << "%" << endl;
	}
	else
	{
		OutFile << "Average of Df: " << 0
			<< "\t Average of Dd: " << 0
			<< "\t Average of Db: " << 0 << endl;
		OutFile << "Df/Db% = " << 0 << "%"
			<< ", Dd/Db% = " << 0 << "%" << endl;
	}
}

void Game::PrintFights()
{
	cout << "\033[34m";
	cout << "=============== BATTLE ROUND  ===============" << endl;
	bool EarthBattle = E_Army->PrintFights();
	bool ALienBattle = A_Army->PrintFights();
	bool AlliedBattle = AL_Army->PrintFights();


	if (!(EarthBattle || ALienBattle || AlliedBattle))
	{
		cout << "\033[34m";
		cout <<"\n\n~~~~SILENCE~ NOTHING HAPPENED ! ~SILENCE~~~~\n\n\n";
		cout << "\033[0m";

	}

}

void Game::Battle()
{
	E_Army->attack();
	A_Army->attack();
	AL_Army->attack();
	E_Army->CalcInfPercentage();

}

void Game::GenerateUnits()
{
	bool GenerateAlienUnits = Generator->WillGenerate();
	bool GenerateEarthUnits = Generator->WillGenerate();
	bool GenerateAlliedUnits = E_Army ->CallAllied() && Generator->WillGenerate();

	if (GenerateAlienUnits)
		for (int i = N; i > 0; --i) // Generate if meet the prob 
		{
			unit* Created = Generator->GenerateUnitAlien(TimeStep, this);
			if (!Created)
			{
				if (mode =='a')
					cout << "---------------- Can't Generate Alien IDs OUT OF RANGE ----------------"; 

				break;
			}
			else if (Created)
				AddUnit(Created);
		}

	if (GenerateEarthUnits)
		for (int i = N; i > 0; --i) // Generate if meet the prob 
		{
			unit* Created = Generator->GenerateUnitEarth(TimeStep, this);
			if (!Created)
			{
				if (mode == 'a')
					cout << "---------------- Can't Generate Earth IDs OUT OF RANGE ----------------";

				break;
			}
			else if (Created)
				AddUnit(Created);
		}

	if (GenerateAlliedUnits)
		for (int i = N; i > 0; --i) // Generate if meet the prob 
		{
			unit* Created = Generator->GenerateUnitAllied(TimeStep, this);
			if (!Created)
			{
				if (mode == 'a')
					cout << "---------------- Can't Generate Allied IDs OUT OF RANGE ----------------";

				break;
			}
			else if (Created)
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
			if (!AddUML(ESDummy))
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
		cout << "\nDelete All Allied Army Units.............";
		delete AL_Army;
		cout << "\nDelete All Dead Units.............";
		delete killedList;

		// Deleting Generator
		delete Generator;
}
