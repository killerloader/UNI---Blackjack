#pragma once
#include "Game.h"

class Person
{
public:
	Person(Game& GmRef);
	~Person();

	void Stand();
	void Hit();

protected:
	Game &GRef;
	Deck* m_myDeck;
};

