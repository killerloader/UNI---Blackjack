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

protected:
	Game &GRef;
	Deck* m_myDeck;
};

