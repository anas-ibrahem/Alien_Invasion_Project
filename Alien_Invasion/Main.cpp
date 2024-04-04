#include "../Game/Game.h"
// from 4001 to 5000 is Drones ID


int main() {

 Game* MainGame = new Game();


 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));
 MainGame->AddUnit(new aMonster(100, 100, 100, 100));
 MainGame->AddUnit(new aSolider(100, 100, 100, 100));
 MainGame->AddUnit(new aDrone(100, 1010, 0, 00));



 MainGame->PrintAliveUnits();

}