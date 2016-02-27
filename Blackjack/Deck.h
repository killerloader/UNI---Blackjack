#pragma once

#include <vector>

//Card class pre-declaration, so that Deck can see Card.
class Card;

//Deck class - Will handle multiple cards for players or for the game deck.
class Deck
{
public:
	Deck(int);
	~Deck();

	void TakeFromDeck(Deck &otherDeck, bool random);

private:
	std::vector<Card> m_myDeck;
};

