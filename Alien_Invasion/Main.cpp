#include "../Game/Game.h"
#include "..\RandGen\RandGen.h"
// from 4001 to 5000 is Drones ID


int main() {

 Game* MainGame = new Game();
 RandGen random(MainGame);
 random.GenerateUnits();
 random.GenerateUnits();
 random.GenerateUnits();
 /*MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));

 MainGame->AddUnit(new eSolider(100, 1010, 0, 00));
 MainGame->AddUnit(new eTank(200, 100, 50, 100));
 MainGame->AddUnit(new eGunnery(100, 100, 100, 100));
 MainGame->AddUnit(new eSolider(100, 1010, 0, 00));
 MainGame->AddUnit(new eTank(200, 129, 50, 100));
 MainGame->AddUnit(new eGunnery(100, 100, 100, 100));
 MainGame->AddUnit(new eSolider(100, 1200, 0, 00));
 MainGame->AddUnit(new eTank(200, 100, 50, 100));
 MainGame->AddUnit(new eGunnery(100, 100, 100, 100));*/


 MainGame->PrintAliveUnits();

}