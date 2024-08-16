#include "Game.h"
using namespace std;

Game::Game() {

	mode = 'a'; // default mode is 'a' // 's' for silent mode	// 'a' for interactive mode
	winner = 'n'; // none 
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

		if (E_Army->GetInfPercentage() == 0)
			 AL_Army->clearArmy(); // Delete Saver Units if Call Allied is false

		GenerateUnits();
		Battle();

		char c = '`';
		if (mode == 'a')
		{
			cout << "\n\n";
			PrintAllStats();

			// Change Mode To Silent Mode Option
			cout << "\n====================================================================================================\n";
			cout << "\n*To continue in Silent mode press s\nPress any other key to continue . . .";
			c = tolower(_getch()); // wait for user to press any key to continue ( s to change to silent mode )

			if (c == 's')
			{
				cout << "\n## Are You Sure You Want To Change To Silent Mode ? --> Press Y to confirm . . . ##\n";
				c = tolower(_getch()); 
				
				if (c == 'y') 
				{
					SetMode('s');
					cout << "Changed To Silent Mode ~SHHHHHHHHHHHHHHHHHH~\n";
				}
			}

		}

		if (TimeStep >= 40) // Wait at least 40 timesteps 
			winner = WL_Check();

	} while (winner == 'n');

	ClearUML(); // Clear UML and move it's units to 
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
	// 
	// if both total = 0 or the Left units are not able to attack each other
	// (following cases) ( Regardless of UML in case of no EH they are not considered )
	// 
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
	while (temp = PickfromUML())
	{
		if (winner == 'e')
			AddUnit(temp);
		else
			AddToKilled(temp);
	}
}

void Game::IncTotalInfectedEarth()
{
	E_Army->IncTotalInfected();
}


void Game::SetMode(char mode)
{
	this->mode = mode;
}

bool Game::AddToKilled(unit*U)
{
	U->setTD(GetTS()); // SET TIME DESTRUCTION


	return killedList->enqueue(U);
}



int Game::GetTS() const
{
	return TimeStep;
}

char Game::GetMode() const
{
	 return mode;
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

	//User enter Input file name
	ifstream inFile("../InputFiles/" + inputfilename);
	while(!inFile.is_open()) // Re Ask If Name is Invalid
	{
		cout << "The Name you entered is invalid ... Enter a valid name" << endl;
		cin >> inputfilename;
		inFile.open("../InputFiles/"+ inputfilename);
	}

	GenParameters P; // Struct to return for RandGen

	//Read N (no of units for each generation)
	inFile >> N;

	//Read Earth Prop Percentage for Each Type
	inFile >> P.EarthPercentage[0] >> P.EarthPercentage[1] >> P.EarthPercentage[2] >>P.EarthPercentage[3];
	//Limit EH if more than 5%
	if (P.EarthPercentage[3] > 5) P.EarthPercentage[3] = 5;
	//Read Alien Prop Percentage for Each Type
	inFile >> P.AlienPercentage[0] >> P.AlienPercentage[1] >> P.AlienPercentage[2];

	//Read Prob of generation
	inFile >> P.prob;

	//Reading Earth Army Ranges
	inFile >> P.E_Power_Range[0];
	inFile >> P.E_Power_Range[1];
	P.E_Power_Range[1] *= -1;
	inFile >> P.E_Health_Range[0];
	inFile >> P.E_Health_Range[1];
	P.E_Health_Range[1] *= -1;
	inFile >> P.E_Capacity_Range[0];
	inFile >> P.E_Capacity_Range[1];
	P.E_Capacity_Range[1] *= -1;

	//Reading Alien Army Ranges
	inFile >> P.A_Power_Range[0];
	inFile >> P.A_Power_Range[1];
	P.A_Power_Range[1] *= -1;
	inFile >> P.A_Health_Range[0];
	inFile >> P.A_Health_Range[1];
	P.A_Health_Range[1] *= -1;
	inFile >> P.A_Capacity_Range[0];
	inFile >> P.A_Capacity_Range[1];
	P.A_Capacity_Range[1] *= -1;


	//Reading Allied Army Ranges
	inFile >> P.AL_Power_Range[0];
	inFile >> P.AL_Power_Range[1];
	P.AL_Power_Range[1] *= -1;
	inFile >> P.AL_Health_Range[0];
	inFile >> P.AL_Health_Range[1];
	P.AL_Health_Range[1] *= -1;
	inFile >> P.AL_Capacity_Range[0];
	inFile >> P.AL_Capacity_Range[1];
	P.AL_Capacity_Range[1] *= -1;


	//Read Infection Probabilty
	double AM_Infect_prob;
	inFile >> AM_Infect_prob;
	aMonster::set_AM_Infect_Prob(AM_Infect_prob);

	//Read InfectionPercentage Thershold
	double InfectThershold = 0;
	inFile >> InfectThershold;
	E_Army->SetInfThershold(InfectThershold);

	//Close File
	inFile.close();

	//Return Data Needed for RangGen (Struct)
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

bool Game::AddtoUML(unit* U)
{
	U->setTj_UML(TimeStep);
	return (E_Army->AddtoUML(U));
}

unit* Game::PickUnit(unit::UnitType type , char PickDir)
{
	// Will return Null From the PickUnit of The armies in case not found
	if(type == unit::SU)
		return AL_Army->PickUnit(type);
	 else if (type == unit::AD || type == unit::AS || type == unit::AM)
		return A_Army->PickUnit(type , PickDir);
	else
		return E_Army->PickUnit(type);

}

int Game::GetUnitCount(unit::UnitType type) const
{
	if (type == unit::AD || type == unit::AS || type == unit::AM)
		return A_Army->GetUnitCount(type);
	else if (type == unit::SU)
		return AL_Army->GetUnitCount(type);
	else
		return E_Army->GetUnitCount(type);
}


unit* Game::PickfromUML()
{
	return E_Army->PickfromUML();
}



void Game::PrintKilledUnits()
{
	cout << "\033[1;31m";
	cout << "\n=============== Killed Units ===============" << endl;

	cout << killedList->getCount() << " units ";
	killedList->print();
	cout << "\n";

	cout << "\033[0m";
}

void Game::WriteFile()
{
	int N_ES_Killed = 0, N_ET_Killed = 0, N_EG_Killed = 0, N_EH_Killed = 0; //N for each type killed Earth
	int N_ES_alive = 0, N_ET_alive = 0, N_EG_alive = 0, N_EH_alive = 0; //N for each type alive Earth

	int N_AS_Killed = 0, N_AD_Killed = 0, N_AM_Killed = 0;  //N for each type killed Alien
	int N_AS_alive = 0, N_AD_alive = 0, N_AM_alive = 0; //N for each type alive Alien

	double ESumDF = 0, ESumDD = 0, ESumDB = 0; // Variables for Durations
	double ASumDF = 0, ASumDD = 0, ASumDB = 0;

	double ASum_alive = 0, ASum_killed = 0, ASum_Total = 0; // Sum Variables
	double ESum_alive = 0, ESum_killed = 0, ESum_Total = 0;

	string outputfilename;
	cout << "\nEnter Output File Name : ex(output.txt)  \n* File Will be Created inside OutputFiles Folder " << endl;
	cin >> outputfilename;
	ofstream OutFile("../OutputFiles/" + outputfilename);

	OutFile << "////////////////// KILLED UNITS DATA /////////////////////\n\n";
	OutFile << "Td  \tID  \tTj  \tDf  \tDd  \tDb" << endl;

	LinkedQueue<unit*> temp; //temp list to stre and return to killed list
	unit* U = nullptr; // temp pointer for unit

	while (killedList->dequeue(U))
	{
		temp.enqueue(U);

		if (U->GetType() != unit::SU) // Exclude SU from Stats
		{
			int Td = U->getTd(); //Get All Times
			int Tj = U->getTj();
			int Ta = U->getTa();

			OutFile << Td << "   \t" << U->getID() << "   \t" << Tj << "   \t" << Ta - Tj << "   \t" << Td - Ta << "   \t" << Td - Tj << endl;

			switch (U->GetType())
			{
			case unit::ES:
				N_ES_Killed++;
				ESumDF += Ta - Tj;
				ESumDD += Td - Ta;
				ESumDB += Td - Tj;
				break;
			case unit::ET:
				N_ET_Killed++;
				ESumDF += Ta - Tj;
				ESumDD += Td - Ta;
				ESumDB += Td - Tj;
				break;
			case unit::EG:
				N_EG_Killed++;
				ESumDF += Ta - Tj;
				ESumDD += Td - Ta;
				ESumDB += Td - Tj;
				break;
			case unit::EH:
				N_EH_Killed++;
				ESumDF += Ta - Tj;
				ESumDD += Td - Ta;
				ESumDB += Td - Tj;
				break;
			case unit::AS:
				N_AS_Killed++;
				ASumDF += Ta - Tj;
				ASumDD += Td - Ta;
				ASumDB += Td - Tj;
				break;
			case unit::AD:
				N_AD_Killed++;
				ASumDF += Ta - Tj;
				ASumDD += Td - Ta;
				ASumDB += Td - Tj;
				break;
			case unit::AM:
				N_AM_Killed++;
				ASumDF += Ta - Tj;
				ASumDD += Td - Ta;
				ASumDB += Td - Tj;
				break;
			default:
				break;
			}
		}
	}

	while (temp.dequeue(U))
		killedList->enqueue(U); // return units to it's original killedlist to delete them at the destructor

	// Calculate Alive - Killed - Sum Variables
	N_ES_alive = E_Army->GetUnitCount(unit::ES);
	N_ET_alive = E_Army->GetUnitCount(unit::ET);
	N_EG_alive = E_Army->GetUnitCount(unit::EG);
	N_EH_alive = E_Army->GetUnitCount(unit::EH);
	N_AS_alive = A_Army->GetUnitCount(unit::AS);
	N_AM_alive = A_Army->GetUnitCount(unit::AM);
	N_AD_alive = A_Army->GetUnitCount(unit::AD);

	ESum_alive = N_ES_alive + N_ET_alive + N_EG_alive + N_EH_alive;
	ESum_killed = N_ES_Killed + N_ET_Killed + N_EG_Killed + N_EH_Killed;
	ESum_Total = ESum_alive + ESum_killed;

	ASum_alive = N_AS_alive + N_AD_alive + N_AM_alive;
	ASum_killed = N_AS_Killed + N_AD_Killed + N_AM_Killed;
	ASum_Total = ASum_alive + ASum_killed;


	// Print Winner
	OutFile << "\n\n";
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
	OutFile << "\n     Finish TimeStep : " << TimeStep;

	// Print Stats For Each Army
	OutFile << "\n\n////////////////// E A R T H  A R M Y /////////////////////\n";

	OutFile << "\nUnit Total Count :\n";
	OutFile << "ES: " << N_ES_alive + N_ES_Killed
			<< "            ET: " << N_ET_alive + N_ET_Killed 
			<< "            EG: " << N_EG_alive + N_EG_Killed 
			<< "            EH: " << N_EH_alive + N_EH_Killed << endl;

	OutFile << "\nUnit Killed Percentage :\n";
	OutFile << "ES%: " << ((N_ES_alive + N_ES_Killed) ? (double)N_ES_Killed / (N_ES_alive + N_ES_Killed) * 100 : 0) << "%";
	OutFile << "            ET%: " << ((N_ET_alive + N_ET_Killed) ? (double)N_ET_Killed / (N_ET_alive + N_ET_Killed) * 100 : 0) << "%";
	OutFile << "            EG%: " << ((N_EG_alive + N_EG_Killed) ? (double)N_EG_Killed / (N_EG_alive + N_EG_Killed) * 100 : 0) << "%";
	OutFile << "            EH%: " << ((N_EH_alive + N_EH_Killed) ? (double)N_EH_Killed / (N_EH_alive + N_EH_Killed) * 100 : 0) << "%";
	OutFile << endl << endl;

	OutFile << "Total Infected ES Percentage : " << ((N_ES_alive + N_ES_Killed) ? E_Army->GetInfTotal() * 100.0 / (N_ES_alive + N_ES_Killed) : 0 )<< "%\n";
	OutFile << "Total Healed Percentage: " << ((ESum_Total) ? unit::GetNumOfHealed() * 100 / ESum_Total : 0) << "%";
	OutFile << endl;

	OutFile << "Total Destructed Percentage: " << ((ESum_Total) ? ESum_killed * 100.0 / ESum_Total : 0) << "%";
	OutFile << endl << endl;

	// Print Durations Avg
	if (ESum_killed) 
	{
		OutFile <<    "Average of Df: " << ESumDF / ESum_killed <<" Ts"
				<< "\t    Average of Dd: " << ESumDD / ESum_killed <<" Ts"
				<< "\t    Average of Db: " << ESumDB / ESum_killed <<" Ts" << endl;

		OutFile <<   "Df/Db% = " << ESumDF * 100.0 / ESumDB << "%"
				<< "    Dd/Db% = " << ESumDD * 100.0 / ESumDB << "%" << endl;
	}
	else
	{
		OutFile << "Average of Df: " << "0 Ts"
			<< "\t    Average of Dd: " << "0 Ts"
			<< "\t    Average of Db: " << "0 Ts" << endl;

		OutFile << "Df/Db% = " << 0 << "%"
			<< "    Dd/Db% = " << 0 << "%" << endl;
	}




	OutFile << "\n\n////////////////// A L I E N  A R M Y /////////////////////\n";

	OutFile << "\nUnit Total Count :\n";
	OutFile <<			   "AS: " << N_AS_alive + N_AS_Killed
			<< "            AD: " << N_AD_alive + N_AD_Killed
			<< "            AM: " << N_AM_alive + N_AM_Killed << endl;

	OutFile << "\nUnit Killed Percentage :\n";
	OutFile << "AS%: " << ((N_AS_alive + N_AS_Killed) ? (double)N_AS_Killed / (N_AS_alive + N_AS_Killed) * 100 : 0) << "%";
	OutFile << "            AD%: " << ((N_AD_alive + N_AD_Killed) ? (double)N_AD_Killed / (N_AD_alive + N_AD_Killed) * 100 : 0) << "%";
	OutFile << "            AM%: " << ((N_AM_alive + N_AM_Killed) ? (double)N_AM_Killed / (N_AM_alive + N_AM_Killed) * 100 : 0) << "%";
	OutFile << endl << endl;

	OutFile << "Total Destructed Percentage: " << ((ASum_Total) ? ASum_killed * 100.0 / ASum_Total : 0) << "%";
	OutFile << endl << endl;


	// Print Durations Avg
	if (ASum_killed) 
	{
		OutFile << "Average of Df: " << ASumDF / ASum_killed <<" Ts"
			<< "\t    Average of Dd: " << ASumDD / ASum_killed<<" Ts"
			<< "\t    Average of Db: " << ASumDB / ASum_killed<<" Ts" << endl;
		OutFile << "Df/Db% = " << ASumDF * 100.0 / ASumDB << "%"
			<< "    Dd/Db% = " << ASumDD * 100.0 / ASumDB << "%" << endl;
	}
	else
	{
		OutFile << "Average of Df: " <<"0 Ts"
			<< "\t    Average of Dd: " <<"0 Ts"
			<< "\t    Average of Db: " <<"0 Ts" << endl;
		OutFile << "Df/Db% = " << 0 << "%"
			<< "    Dd/Db% = " << 0 << "%" << endl;
	}

	cout << "Output File Generated Successfully...\n";
	//Close the file
	OutFile.close();
}

void Game::PrintFights()
{
	cout << "\033[34m";
	cout << "=============== BATTLE ROUND  ===============" << endl;
	bool EarthBattle = E_Army->PrintFights();
	bool ALienBattle = A_Army->PrintFights();
	bool AlliedBattle = AL_Army->PrintFights();
	cout << "\033[0m";


	if (!(EarthBattle || ALienBattle || AlliedBattle))
	{
		cout << "\033[34m";
		cout <<"~~~~SILENCE~ NOTHING HAPPENED ! ~SILENCE~~~~\n";
		cout << "\033[0m";

	}

}

void Game::Battle()
{
	E_Army->attack();
	E_Army->SpreadInfection();

	A_Army->attack();
	AL_Army->attack();
	
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
	cout << "====================================================================================================\n";
	cout << "Current TimeStep : " << TimeStep << endl << endl;
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
			if (!AddtoUML(ESDummy))
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
