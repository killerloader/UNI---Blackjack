#include "Card.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <math.h>

Card::Card(int cardId, Game *gamePtr_)
{
	m_gamePtr = gamePtr_;
	m_myName = nullptr;
	//m_myName[0] = 5;
	m_cardId = cardId;
	//myName = new char[strlen(NewName) + 1];//+1 to include (\0) null terminator
	generateName(cardId);
	//strcpy(myName, NewName);
	std::cout << m_myName << std::endl;
}

Card::Card(Card &Ocard)
{
	*this = Ocard;//Use = copy operator to copy Ocard into this card.
	//TODO: Create proper copy constructor.
}

void Card::generateName(int cardID)
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

	//This might be a more efficient way of doing it, however itoa is more C
	//It would be premature optimization to implement this.
	/*char texName[8];
	strcpy_s(texName,8,"Card:");
	char itoaBuffer[3];
	_itoa_s(cardID, itoaBuffer, 3, 10);
	strcat_s(texName, 8, itoaBuffer);*/

	std::stringstream tempstream;
	tempstream << "Card:" << cardID;
	m_mySprite.setTexture(*Resources::instance().findTexture(tempstream.str().c_str()));
}

int Card::getCardId()
{
	return m_cardId;
}

int Card::getCardValue()
{
	return m_cardNum;
}

const char* Card::getName()
{
	return m_myName;
}

Card::~Card()
{
	if (m_myName != nullptr)//Defined in constructor so should not be a problem.
		delete[] m_myName;
}