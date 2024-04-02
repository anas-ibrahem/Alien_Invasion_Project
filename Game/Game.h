#include "../DS/LinkedQueue.h"
#include "../ArmiesHeaders/AlienArmy/AlienArmy.h"


class Game {
private:
	int TimeStep;
	LinkedQueue<unit*> killedList;
	AlienArmy A_Army;
	//EarthArmy E_Army;
	
public :
	Game();
	int GetTime() const;
	bool IncreaseTime(int Duration);
	bool ReadFile(); // To Be implemented to Edit Values of n, ES_Per, AS_Per, ET_Per, EG_Per, AM_Per , AD_Per;
	bool WriteFile(); // To Be implemented
	bool AddUnit(unit* unit);

};