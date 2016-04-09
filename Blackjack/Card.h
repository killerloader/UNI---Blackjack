#pragma once

#include<SFML/Graphics.hpp>

/*
Card.h/ Card.cpp
Holds the information of a card, its sprite and its name.
Can also generate this information.
*/

class Game;

class Card
{
public:
	Card(int cardId, Game &gameRef);//Main constructor
	Card(Card &Ocard, Game &gameRef);//Copy constructor.
	void operator=(Card &Ocard);	//copy assignment operator.
	~Card();						//Destructor.
	int getCardNum();				//Gets the value of the current card.
	const char* getName();			//Gets the name of the card. ("King of Diamonds", etc)
	int getCardId();				//Gets the card Id (0 to 51)
	sf::Sprite& getSprite();

private:
	void generateCard(int cardID);	//Creates the card (sets the texture and creates the name)
	int m_cardId;					//Card ID (0 to 51)
	int m_cardNum;					//2 - 10, ace, jack, queen or king. (0-12)
	int m_cardSuit;					//Card suit (0 to 3)
	char *m_myName;					//Stored name of card.
	Game &m_gameRef;				//Pointer to game class.
	sf::Sprite m_mySprite;			//Sprite of card (not a copy of its texture though)
};

