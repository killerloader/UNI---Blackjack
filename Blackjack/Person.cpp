#include "Person.h"
#include "Deck.h"
#include "Game.h"

#include <iostream>

Person::Person(Game& GmRef) : m_gameRef(GmRef)
{
	m_myDeck = new Deck(m_gameRef);
	m_standing = false;
}

Person::~Person()
{
	delete m_myDeck;
}

//Will stand if not standing, or stop standing if already standing.
void Person::stand()
{
	m_standing = true;
}

void Person::reset()
{
	m_myDeck->clearDeck();
	m_myDeck = new Deck(m_gameRef);
	m_standing = false;
}

void Person::hit()
{
	m_myDeck->takeFromDeck(*m_gameRef.getMainDeck());
}

bool Person::isBust()
{
	return (m_myDeck->calculateTotal() > 21);
}

bool Person::isStanding()
{
	return m_standing;
}

Deck* Person::getDeck()
{
	return m_myDeck;
}