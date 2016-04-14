#include "Card.h"
#include "Game.h"

#include <iostream>
#include <sstream>
#include <math.h>

//Card constructor, generates a name based on its card ID, and gets its texture based on its card ID.
Card::Card(const int &cardId, Game &gameRef) : m_gameRef(gameRef)
{
	m_myName = nullptr;
	m_cardID = cardId;
	generateCard(cardId);
}

//Copy constructor.
//Creates new copies of everything. (Uses same texture in resources)
Card::Card(Card &otherCard, Game &gameRef) : m_gameRef(gameRef)
{
	*this = otherCard;//Use = copy operator to copy Ocard into this card.
}

//Returns a refernece to the card's sprite.
sf::Sprite& Card::getSprite()
{
	return m_mySprite;
}

//This function generates a name for the card and sets its sprite to the corrosponding texture in the game resources.
void Card::generateCard(const int &cardID)
{
	//Create buffers and card variables.
	char* suit;
	char* card;
	int totalLen(0), suitLen(0), cardLen(0);
	m_cardID = cardID;
	m_cardSuit = m_cardID / 13;
	m_cardNum = m_cardID - m_cardSuit*13;

	//Find the name of which suit the card is in.
	switch (m_cardSuit)
	{
	case 0:suit = new char[6]{ "clubs" }; break;
	case 1:suit = new char[7]{ "spades" }; break;
	case 2:suit = new char[7]{ "hearts" }; break;
	case 3:suit = new char[9]{ "diamonds" }; break;
	default:suit = new char[6]{ "ERROR" }; break;
	}

	//Add to the total string length.
	suitLen = strlen(suit);
	totalLen += strlen(suit);
	
	//Finds the name of te card number.
	switch (m_cardNum)
	{
	case 0:card = new char[4]{ "Ace" }; break;
	case 1:card = new char[2]{ "2" }; break;
	case 2:card = new char[2]{ "3" }; break;
	case 3:card = new char[2]{ "4" }; break;
	case 4:card = new char[2]{ "5" }; break;
	case 5:card = new char[2]{ "6" }; break;
	case 6:card = new char[2]{ "7" }; break;
	case 7:card = new char[2]{ "8" }; break;
	case 8:card = new char[2]{ "9" }; break;
	case 9:card = new char[3]{ "10" }; break;
	case 10:card = new char[5]{ "Jack" }; break;
	case 11:card = new char[6]{ "Queen" }; break;
	case 12:card = new char[5]{ "King" }; break;
	default:card = new char[6]{ "ERROR" }; break;
	}

	//Add to the total string length.
	cardLen = strlen(card);
	totalLen += strlen(card);//Don't include null terminator as we wilkl only need that at the end.
	totalLen += strlen(" of ") + 1;//The extra length for " of " and the null terminator.

	//Delete old name and create new one.
	if (m_myName != nullptr)
		delete[] m_myName;//Delete old card name if this is called for a second time (unlikely)

	m_myName = new char[totalLen];
	strcpy_s(m_myName, totalLen, card);
	strcat_s(m_myName, totalLen, " of ");
	strcat_s(m_myName, totalLen, suit);

	//Delete temporary buffers.
	delete[] card;
	delete[] suit;

	//Find the texture that corresponds to this card from resources by searching for a string.
	//This string first needs to be created using a stream.
	std::stringstream tempstream;
	tempstream << "Card:" << cardID;
	m_mySprite.setTexture(*Resources::instance().findTexture(tempstream.str().c_str()));
}

//Gets the ID of the card (0-51) (all cards in a deck)
int Card::getCardId()
{
	return m_cardID;
}

//Retunrs the number of the card (0 to 12 AKA: Ace, 2-10, Jack, Queen, King)
int Card::getCardNum()
{
	return m_cardNum;
}

//Returns the name of the card. (pointer)
const char* Card::getName()
{
	return m_myName;
}

//Copy constructor.
//Copies information from one card to this one.
//Might not be very useful when all cards are held as pointers and their pointer is all that gets transferred.
void Card::operator=(Card &otherCard)//Also copy constructor
{
	//Delete current name if it has one.
	if (m_myName != nullptr)
		delete[] m_myName;//Delete old card name if it is already created (pretty much certain)

	//Create a new char array for the name.
	m_myName = new char[strlen(otherCard.getName()) + 1];
	
	//Copy other name into this one.
	strcpy_s(m_myName, strlen(otherCard.getName()) + 1, otherCard.getName());

	//Copy other stuff.
	m_cardID = otherCard.m_cardID;
	m_cardNum = otherCard.m_cardNum;
	m_cardSuit = otherCard.m_cardSuit;
	m_mySprite = otherCard.m_mySprite;
}

//Card destructor.
//Destroys the name.
Card::~Card()
{
	if (m_myName != nullptr)//Defined in constructor so should not be a problem.
		delete[] m_myName;
}