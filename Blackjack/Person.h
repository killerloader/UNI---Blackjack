#pragma once

//Needed?
class Game;
class Deck;
class Card;

class Person
{
public:
	Person(Game& GmRef);
	~Person();

	void stand();
	void reset();
	Card* hit();
	bool isBust();
	bool isStanding();
	Deck* getDeck();

protected:
	Game &m_gameRef;
	Deck* m_myDeck;
	bool m_standing;
};

