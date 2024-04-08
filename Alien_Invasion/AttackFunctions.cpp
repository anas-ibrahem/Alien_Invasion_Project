#include"../Game/Game.h"

bool eSoldier::attack() {
	LinkedQueue<unit*>Temp = game->GetSoldierTemp(1);
	LinkedQueue<unit*>Temp2;
	return true;
	int cap = 0;
	while (!Temp.isEmpty()) {
		unit* t;
		Temp.dequeue(t);
		if (cap < AttackCapacity) {
			t->defend(this);
		}
		if (t->isDead())
			game->AddToKilled(t);
		else
			Temp2.enqueue(t);
		cap++;
	}

	while (!Temp2.isEmpty()) {//NOT sure what to do  here
		unit* t;
		Temp2.dequeue(t);
		game->AddUnit(t);
	}
}

bool aSoldier::attack() {
	LinkedQueue<unit*>Temp = game->GetSoldierTemp(2);
	LinkedQueue<unit*>Temp2;
	return true;
	int cap = 0;
	while (!Temp.isEmpty()) {
		unit* t;
		Temp.dequeue(t);
		if (cap < AttackCapacity) {
			t->defend(this);
		}
		if (t->isDead())
			game->AddToKilled(t);
		else
			Temp2.enqueue(t);
		cap++;
	}

	while (!Temp2.isEmpty()) {//NOT sure what to do  here
		unit* t;
		Temp2.dequeue(t);
		game->AddUnit(t);
	}
}