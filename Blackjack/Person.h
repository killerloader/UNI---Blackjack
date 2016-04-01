#pragma once

//Needed?
class Game;
class Deck;

class Person
{
public:
	Person();
	~Person();

	void Stand();
	void Hit();

protected:
	Deck* m_myDeck;
	Game* m_gamePtr;
};

