#pragma once

/*
	Card.h/ Card.cpp
		Holds the information of a card, its sprite and its name.
		Can also generate this information.
*/

#include<SFML/Graphics.hpp>

class Game;

class Card
{
public:
	Card(const int &cardID);//Main constructor
	Card(Card &otherCard);//Copy constructor.
	~Card();						//Destructor.
	void operator=(Card &otherCard);	//copy assignment operator.
	const char* getName();			//Gets the name of the card. ("King of Diamonds", etc)
	int getCardId();				//Gets the card Id (0 to 51)
	int getCardNum();				//Gets the value of the current card.
	sf::Sprite& getSprite();		//Returns the sprite of the card.

private:
	void generateCard(const int &cardID);//Creates the card (sets the texture and creates the name)
	int m_cardID;					//Card ID (0 to 51)
	int m_cardNum;					//2 - 10, ace, jack, queen or king. (0-12)
	int m_cardSuit;					//Card suit (0 to 3)
	char *m_myName;					//Stored name of card.
	sf::Sprite m_mySprite;			//Sprite of card (not a copy of its texture though)
};

