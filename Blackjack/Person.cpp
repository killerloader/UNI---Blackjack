#include "Person.h"
#include "Deck.h"
#include "Game.h"

#include <iostream>

Person::Person(Game& GmRef) : m_gameRef(GmRef)
{
	m_myDeck = new Deck(GmRef);
}

Person::~Person()
{
	delete m_myDeck;
}

void Person::Stand()
{

}

void Person::Hit()
{
	m_myDeck->takeFromDeck(*m_gameRef.getMainDeck());
}

Deck* Person::getDeck()
{
	return m_myDeck;
}