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

bool eTank::attack() {
	//if()condition will do it 14/4/2024
	DynamicArray<unit*>Monsters = game->GetMonsterTemp();
	int cap = 0;
	while (cap != AttackCapacity) {
		unit* t;
		t = Monsters.Pick();
		if (t->defend(this)) {
			Monsters.remove(t);
			game->AddToKilled(t);
		}
		cap++;
	}

	//else will make it attack A soldiers
}







































































//A_Army attack

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