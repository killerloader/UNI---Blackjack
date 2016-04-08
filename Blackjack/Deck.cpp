#include "Deck.h"
#include "Card.h"
#include "Game.h"

#include <iostream>

Deck::Deck(Game *gamePtr_)
{
	m_gamePtr = gamePtr_;
}

Deck::~Deck()
{
	//Delete cards in deck.
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		delete m_myDeck[i];
}

//TakeFromDeck() will take cards from another deck (removing them from the other deck and adding them to this deck)
//could also call this 'drawCard'
void Deck::takeFromDeck(Deck &otherDeck)
{
	//Other deck is empty, so can't take anything.
	if (otherDeck.m_myDeck.size() <= 0)
		return;

	//Create temporary copy of last card pointer for the other deck.
	Card* tempCardPtr = otherDeck.m_myDeck[otherDeck.m_myDeck.size() - 1];

	//Remove last card from other deck.
	otherDeck.m_myDeck.erase(otherDeck.m_myDeck.begin() + otherDeck.m_myDeck.size() - 1);

	//Add last card to this deck.
	m_myDeck.push_back(tempCardPtr);
}

//Calculate the total of the cards.
//This is a separate function and not just a variable that iterates
//due to the ace being either 1 or 11
int Deck::calculateTotal() const
{
	int totalValue = 0;

	//Get cost of all cards discluding aces.
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
	{
		//Get the number of the card (0 to 12) and plus one (1 to 13) so that 2 to 10 are worth thisValue.
		int thisValue = m_myDeck[i]->getCardNum() + 1;
		if (thisValue != 1)//Not an ace
		{
			if (thisValue > 10)//clamp 11, 12 and 13 (J/K/Q) down to 10
				thisValue = 10;//Jack, King and Queen are worth 10.

			totalValue += thisValue;
		}
	}

	//Get cost of aces as ones
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		if (m_myDeck[i]->getCardNum() == 0)//Is an ace
			totalValue += 1;

	//Check if we can treat any of the aces as elevens.
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		if (m_myDeck[i]->getCardNum() == 0)//Is an ace
		{
			//Alrady counted as 1, so +10 to make it count as 11.
			if (totalValue + 10 > 21)
				break;//We cannot change this as it will cause the player to go over 21.
			else
				totalValue += 10;
		}

	return totalValue;
}

//Might not be used as we may only ever move from deck to deck.
//Creates a new card out of nothingness
void Deck::addCard(int CID)
{
	//Can't use emplace_back because is a vector of pointers.
	m_myDeck.push_back(new Card(5, m_gamePtr));
}

//Essentially the same as the subscript operator.
Card* Deck::getCard(unsigned int ID) const
{
	//Just use the subscript operator.
	return (*this)[ID];
}

//Returns a pointer to a card at a specific place in the deck.
Card* Deck::operator[] (unsigned int ID) const
{
	if (ID>=m_myDeck.size())
		return nullptr;
	return m_myDeck[ID];
}

//Draws each card in the deck to the screen.
void Deck::drawDeck()
{
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
	{
		m_myDeck[i]->getSprite().setPosition(i*20,400);
		m_gamePtr->drawItem(m_myDeck[i]->getSprite());
	}
}

//Will generate the main deck by getting 52 cards and randomizing the order.
void Deck::generateMainDeck()
{
	//Clear this deck just in case.
	clearMyDeck();
	
	//Create the cards in order in the array.
	std::cout << "Creating main deck and generating cards..." << std::endl;

	//Iterate through every card ID.
	for (int i = 0;i < 52; i++)
	{
		//Generate card image
		Resources::instance().renderCard(i);

		//Create card (Constructor will assign card image to its sprite, so must be done in this order)
		m_myDeck.push_back(new Card(i, m_gamePtr));
	}

	std::cout << "Done!" << std::endl;

	//Shuffle the deck.
	shuffle();
}

void Deck::shuffle()
{
	std::vector<Card*> tempDeck(m_myDeck);
	m_myDeck.clear();
	while (tempDeck.size() > 0)
	{
		//Get a random card from the deck.
		int TakeRand = rand() % tempDeck.size();

		//Add this card to this deck.
		m_myDeck.push_back(tempDeck[TakeRand]);//ID or just use copy constructor? (and make own constructor, should use rule of three)

		//Remove this card from other deck. (Don't delete, because the memory is being transferred to this deck)
		tempDeck.erase(tempDeck.begin() + TakeRand);
	}
}

void Deck::clearMyDeck()
{
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		delete m_myDeck[i];

	m_myDeck.clear();
}
