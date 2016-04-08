#pragma once

//Needed?
class Game;
class Deck;

class Person
{
public:
	Person(Game& GmRef);
	~Person();

	void Stand();
	void Hit();
	Deck* getDeck();

protected:
	Game &m_gameRef;
	Deck* m_myDeck;
};

