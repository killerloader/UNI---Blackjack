#include "Person.h"
#include "Deck.h"
#include "Game.h"

#include <iostream>

//Constructor, sets status to default (not standing)
Person::Person()
{
	m_myDeck = new Deck();
	m_standing = false;
}

//Destructor, deletes their deck.
Person::~Person()
{
	delete m_myDeck;
}

//Will stand if not standing, or stop standing if already standing.
void Person::stand()
{
	m_standing = true;
}

//Resets the person, resetting their deck and stops them from standing.
void Person::reset()
{
	m_myDeck->clearDeck();
	m_standing = false;
}

//Takes a card from the main deck and returns a pointer to this card.
Card* Person::hit()
{
	return m_myDeck->takeFromDeck(*Game::instance().getMainDeck());
}

//Returns if the person is bust or not.
bool Person::isBust()
{
	return (m_myDeck->calculateTotal() > 21);
}

//Returns if the person is standing or not.
bool Person::isStanding()
{
	return m_standing;
}

//Returns the person's deck.
Deck* Person::getDeck()
{
	return m_myDeck;
}