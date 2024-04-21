#include "../Game/Game.h"
#include <iostream>
#include <conio.h>


int main() {

	int i = 50; // loop for 50 times as requested
	Game MainGame;// In Constructor we call Readfile


	do {	


	MainGame.GenerateUnits();
	
	MainGame.TestCode();
	cout << "\n\n";

	MainGame.PrintAllStats();

	cout << "\n\nPress any key to continue" << endl;

	//_getch(); // wait for user to press any key to continue

	MainGame.NextTS();
	cout << "\n\n\n\n";


	} while (--i);

}