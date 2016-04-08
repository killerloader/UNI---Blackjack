#include "Card.h"
#include "Game.h"

#include <iostream>
#include <sstream>
#include <math.h>

Card::Card(int cardId, Game &gameRef) : m_gameRef(gameRef)
{
	m_myName = nullptr;
	m_cardId = cardId;
	generateCard(cardId);
}

Card::Card(Card &Ocard, Game &gameRef) : m_gameRef(gameRef)
{
	*this = Ocard;//Use = copy operator to copy Ocard into this card.
}

sf::Sprite& Card::getSprite()
{
	return m_mySprite;
}

//This function generates a name for the card and sets its sprite to the corrosponding texture in the game resources.
void Card::generateCard(int cardID)
{
	char* suit_;
	char* card_;
	int totalLen(0), suitLen(0), cardLen(0);
	m_cardId = cardID;
	m_cardSuit = m_cardId / 13;
	m_cardNum = m_cardId - m_cardSuit*13;

	//clubs, spades, hearts, diamonds
	switch (m_cardSuit)
	{
	case 0:suit_ = new char[6]{ "clubs" }; break;
	case 1:suit_ = new char[7]{ "spades" }; break;
	case 2:suit_ = new char[7]{ "hearts" }; break;
	case 3:suit_ = new char[9]{ "diamonds" }; break;
	default:suit_ = new char[6]{ "ERROR" }; break;
	}

	suitLen = strlen(suit_);
	totalLen += strlen(suit_);
	
	switch (m_cardNum)
	{
	case 0:card_ = new char[4]{ "Ace" }; break;
	case 1:card_ = new char[2]{ "2" }; break;
	case 2:card_ = new char[2]{ "3" }; break;
	case 3:card_ = new char[2]{ "4" }; break;
	case 4:card_ = new char[2]{ "5" }; break;
	case 5:card_ = new char[2]{ "6" }; break;
	case 6:card_ = new char[2]{ "7" }; break;
	case 7:card_ = new char[2]{ "8" }; break;
	case 8:card_ = new char[2]{ "9" }; break;
	case 9:card_ = new char[3]{ "10" }; break;
	case 10:card_ = new char[5]{ "Jack" }; break;
	case 11:card_ = new char[6]{ "Queen" }; break;
	case 12:card_ = new char[5]{ "King" }; break;
	default:card_ = new char[6]{ "ERROR" }; break;
	}

	cardLen = strlen(card_);
	totalLen += strlen(card_);//Don't include null terminator as we wilkl only need that at the end.
	totalLen += strlen(" of ") + 1;//The extra length for " of " and the null terminator.

	if (m_myName != nullptr)
		delete[] m_myName;//Delete old card name if this is called for a second time (unlikely)

	m_myName = new char[totalLen];
	strcpy_s(m_myName, totalLen, card_);
	strcat_s(m_myName, totalLen, " of ");
	strcat_s(m_myName, totalLen, suit_);

	delete[] card_;
	delete[] suit_;

	std::stringstream tempstream;
	tempstream << "Card:" << cardID;
	m_mySprite.setTexture(*Resources::instance().findTexture(tempstream.str().c_str()));
}

int Card::getCardId()
{
	return m_cardId;
}

int Card::getCardNum()
{
	return m_cardNum;
}

const char* Card::getName()
{
	return m_myName;
}

//Copy constructor.
//Copies information from one card to this one.
//Might not be very useful when all cards are held as pointers and their pointer is all that gets transferred.
void Card::operator=(Card &Ocard)//Also copy constructor
{
	//Delete current name if it has one.
	if (m_myName != nullptr)
		delete[] m_myName;//Delete old card name if it is already created (pretty much certain)

	//Create a new char array for the name.
	m_myName = new char[strlen(Ocard.getName()) + 1];
	
	//Copy other name into this one.
	strcpy_s(m_myName, strlen(Ocard.getName()) + 1, Ocard.getName());

	//Copy other stuff.
	m_cardId = Ocard.m_cardId;
	m_cardNum = Ocard.m_cardNum;
	m_cardSuit = Ocard.m_cardSuit;
	m_mySprite = Ocard.m_mySprite;
}

Card::~Card()
{
	if (m_myName != nullptr)//Defined in constructor so should not be a problem.
		delete[] m_myName;
}