#pragma once

/*
	ToDO:
		- Overload [] (subscript) operator to  get cards in deck.
*/

#include <vector>

//Card/ Game class pre-declaration.
class Card;
class Game;

//Deck class - Will handle multiple cards for players or for the game deck.
class Deck
{
public:
	Deck(Game *gamePtr_);
	~Deck();

	void takeFromDeck(Deck &otherDeck, int ID = -1);
	void generateMainDeck();
	void clearMyDeck();
	int getCard(unsigned int ID) const;
	int getCardAmount() const;
	const char* getCardName(unsigned int ID) const;
	void addCard(int CID);//Could be reference to a pointer, but not much point.
	int calculateTotal() const;

	Game *m_gamePtr;
private:
	std::vector<Card*> m_myDeck;
};

