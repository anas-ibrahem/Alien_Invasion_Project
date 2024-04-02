#include "../Game/Game.h"
// from 4001 to 5000 is Drones ID


int main() {

	aDrone D1(10, 90, 10, 20);
	aDrone D2(10, 90, 10, 100);
	aDrone D3(10, 10, 10, 10);
	D1.defend(&D2);
	cout << D1.getHealth();


}