#include "Game.h"

using namespace std;


Game::Game() {

	TimeStep = 1;

}

int Game::GetTime() const
{
	return TimeStep;
}

bool Game::IncreaseTime(int Duration)
{
	TimeStep += Duration;
	return true;
}

bool Game::AddUnit(unit* unit)
{
	if ( (unit->GetType() == AD || unit->GetType() == AS ) || unit->GetType() == AM )
	{
		A_Army.AddUnit(unit);
	}
	else
	{
		//E_Army.AddUnit(unit);
	}
	return 1;
}

void Game::PrintAliveUnits()
{
	A_Army.PrintAliveUnits();
	//E_army 
}



// Here Temporary Implementation for Print Function until fixing the template issue // Needs a meeting to discuss the issue
template<>
bool DoubleLinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	DoubleNode<unit*>* ptr = frontPtr;
	cout << "[";
	while (ptr)
	{
		cout << ptr->getItem()->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ","; // Not Last Element
	}

	return true;

}

template<>
bool LinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	Node<unit*>* ptr = frontPtr;
	cout << "[";
	while (ptr)
	{
		cout << ptr->getItem()->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ","; // Not Last Element
	}

	return true;

}
