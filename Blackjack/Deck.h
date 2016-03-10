#pragma once

#include <vector>

//Card class pre-declaration, so that Deck can see Card.
class Card;

//Deck class - Will handle multiple cards for players or for the game deck.
class Deck
{
public:
	Deck();
	~Deck();

	void takeFromDeck(Deck &otherDeck, int ID = -1);
	void generateMainDeck();
	void clearMyDeck();
	int getCard(int ID);
	int getCardAmount();
	const char* getCardName(int ID);
	Card* takeCard();
	void addCard(Card*);//Could be reference to a pointer, but not much point.
	int calculateTotal();

private:
	std::vector<Card*> m_myDeck;
};

