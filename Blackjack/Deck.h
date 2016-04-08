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
	Deck(Game *gamePtr_);								//Constructor (takes pointer to game class)
	~Deck();											//Destructor
	void shuffle();										//Shuffles the cards in the deck.
	void takeFromDeck(Deck &otherDeck);					//Takes a card from another deck, and adds it to this one.
	void generateMainDeck();							//Generates the main deck (should only be used once)
	void clearMyDeck();									//Empties the deck and deletes everything inside.
	void drawDeck();									//draws the cards in the deck to the game surface.
	void addCard(int CID);								//Could be reference to a pointer, but not much point.
	int calculateTotal() const;							//Finds the total worth of the cards in the deck (considers Aces as 1 or 11)
	Card *getCard(unsigned int ID) const;				//Gets a pointer to a card at a specific place.
	Card* operator[] (unsigned int ID) const;			//Subscript operator overload
	Game *m_gamePtr;									//Pointer to game class.

private:
	std::vector<Card*> m_myDeck;
};

