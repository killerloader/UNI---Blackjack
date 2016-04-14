#pragma once

/*
	Person.h/ Person.cpp
		Base class of a blackjack player.
		Pretty much handles what a play would do, hitting and standing.
		The class holds a deck (which is a hand of cards)
		And it holds their status (whether they are standing or bust or neither)
*/

class Game;
class Deck;
class Card;

class Person
{
public:
	Person(Game& gameRef);	//Constructor, uses reference of main game class.
	~Person();				//Destructor, deletes deck.
	void stand();			//Sets the person to standing.
	void reset();			//Resets the player (resets deck and stops standing)
	bool isBust();			//Returns true if the person's deck value is over 21. (if they are bust)
	bool isStanding();		//Returns if the person is standing.
	Deck* getDeck();		//Returns a pointer to the person's deck.
	Card* hit();			//Takes a card from the game deck and adds it to their deck (also returns a pointer to the card they took)

protected:
	Game &m_gameRef;		//Main game class reference.
	Deck* m_myDeck;			//Pointer to own deck/ hand.
	bool m_standing;		//If the person is standing or not.
};

