#include "Person.h"
#include "Deck.h"
#include "Game.h"
#include <iostream>

Person::Person(Game& GmRef) : GRef(GmRef)
{
	m_myDeck = new Deck();
}

Person::~Person()
{
	if(m_myDeck!=nullptr)
		delete m_myDeck;
}

void Person::Stand()
{

}

void Person::Hit()
{
	m_myDeck->takeFromDeck(*GRef.getGameDeck());
}