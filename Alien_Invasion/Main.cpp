#include "../Game/Game.h"
// from 6001 to 7000 is Drones ID



int main() {

	aDrone D1(10 , 10 , 10 , 10);
	aDrone D2(10, 10, 10, 10);
	aDrone D3(10, 10, 10, 10);
	Game Games123s ;

	cout << D1.GetId() << D2.GetId() << D3.GetId();


}