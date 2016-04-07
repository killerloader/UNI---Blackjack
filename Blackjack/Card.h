#pragma once

#include<SFML/Graphics.hpp>

class Game;

/*
Card.h/ Card.cpp
	
*/

class Card
{
public:
	Card(int cardId, Game *gamePtr_);//Main constructor
	Card::Card(Card &Ocard);		//Copy constructor.
	void operator=(Card &Ocard);	//copy assignment operator.
	~Card();						//Destructor.
	int getCardValue();				//Gets the value of the current card.
	const char* getName();			//Gets the name of the card. ("King of Diamonds", etc)
	int getCardId();				//Gets the card Id (0 to 51)

private:
	void generateName(int cardID);	//Creates the name of the card
	int m_cardId;					//Card ID (0 to 51)
	int m_cardNum;					//2 - 10, ace, jack, queen or king. (0-12)
	int m_cardSuit;					//Card suit (0 to 3)
	char *m_myName;					//Stored name of card.
	Game *m_gamePtr;				//Pointer to game class.
	sf::Sprite m_mySprite;			//Sprite of card (not a copy of its texture though)
};

