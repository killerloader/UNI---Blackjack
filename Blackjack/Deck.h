#pragma once

/*
	Deck.h/ Deck.cpp
		Is a container that acts like a deck of cards, you can take cards from 
		a deck and add it to another.
		Also has other functions that help with drawing the deck.
*/

#include <SFML/Graphics.hpp>

#include <vector>

class Card;
class Game;

//Deck class - Will handle multiple cards for players or for the game deck.
class Deck
{
public:
	Deck(Game &gameRef);							//Constructor (takes pointer to game class)
	~Deck();										//Destructor
	void shuffle();									//Shuffles the cards in the deck.
	void generateMainDeck();						//Generates the main deck (should only be used once)
	void clearDeck();								//Empties the deck and deletes everything inside.
	void drawDeck(int x, int y, int separation);	//draws the cards in the deck to the game surface.
	void addCard(int cardID);						//Could be reference to a pointer, but not much point.
	int getWidth(int separation);					//Returns the width of the drawn deck.
	int getHeight();								//Returns the height of the deck/ a single card.
	unsigned int getSize();							//Returns the amount of cards in the deck.
	int calculateTotal();							//Finds the total worth of the cards in the deck (considers Aces as 1 or 11)
	Card* getCard(unsigned int ID) const;			//Gets a pointer to a card at a specific place.
	Card* operator[] (unsigned int ID) const;		//Subscript operator overload
	Card* takeFromDeck(Deck &otherDeck);			//Takes a card from another deck, and adds it to this one.

private:
	Game &m_gameRef;					//Reference to game class.
	std::vector<Card*> m_myDeck;		//Vector (dynamic array) that holds pointers to each card in the deck.
	sf::RectangleShape m_valueRect;		//The rectangle that contains the total text.
	sf::Text m_totalText;				//A cached version of the total, but in sf::Text format (drawable)
	int m_cachedTotal;					//A cached version of the total, so it does not need to be calcualted every time.
	bool m_totalChanged;				//A check to see if total needs to be recalculated.
};

