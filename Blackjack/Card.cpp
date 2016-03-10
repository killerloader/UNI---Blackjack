#include "Card.h"
#include <iostream>
#include <math.h>

Card::Card(int cardId)
{
	m_myName = nullptr;
	//m_myName[0] = 5;
	m_cardId = cardId;
	//myName = new char[strlen(NewName) + 1];//+1 to include (\0) null terminator
	generateName(cardId);
	//strcpy(myName, NewName);
	std::cout << m_myName << std::endl;
}

void Card::generateName(int cardID)
{
	char* suit_;
	int totalLen = 0;
	//clubs, spades, hearts, diamonds
	switch ((int)floor((float)cardID / 13))
	{
	case 0:suit_ = new char[6]{ "clubs" }; break;
	case 1:suit_ = new char[7]{ "spades" }; break;
	case 2:suit_ = new char[7]{ "hearts" }; break;
	case 3:suit_ = new char[9]{ "diamonds" }; break;
	default:suit_ = new char[6]{ "ERROR" }; break;
	}

	int suitLen = strlen(suit_);
	totalLen += strlen(suit_);
	char* card_;

	switch (cardID - (int)floor((float)cardID / 13) * 13)
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

	int cardLen = strlen(card_);
	totalLen += strlen(card_);//Don't include null terminator as we wilkl only need that at the end.
	totalLen += strlen(" of ") + 1;//The extra length for spaces, "of" and the null terminator.

	if (m_myName != nullptr)
		delete[] m_myName;

	m_myName = new char[totalLen];
	strcpy_s(m_myName, totalLen, card_);
	strcat_s(m_myName, totalLen, " of ");
	strcat_s(m_myName, totalLen, suit_);

	delete[] card_;
	delete[] suit_;
}

int Card::getCardId()
{
	return m_cardId;
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