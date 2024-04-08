
#include "../Game/Game.h"
#include <iostream>
#include <conio.h>
// from 4001 to 5000 is Drones ID


int main() {

	int i = 50; // loop for 50 times as requested
	Game MainGame;// In Constructor we call Readfile


	do {	


	MainGame.GenerateUnits();
	
	int X = rand() % 100 + 1;



	if (X <= 10) {} // 
	else if (X <= 20) {}
	else if (X <= 30) {}
	else if (X <= 40) {}
	else if (X <= 50) {}
	else if (X <= 60) {}
	


	MainGame.PrintAllStats();

	cout << "Press any key to continue" << endl;

	_getch(); // wait for user to press any key to continue

	MainGame.NextTS();
	cout << "\n\n\n\n";


	} while (--i);

}