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

}

//TakeFromDeck() will take cards from another deck (removing them from the other deck and adding them to this deck)
//If ID is left as -1, it will take the last card from the deck.
//otherwise it will take the card at the index "ID" in the vector.
//could also call this 'drawCard'
//Will remove a card from this deck and return a pointer to its memory.
//If this is used the in wrong place, the memory of the card will never get deleted, as it will return the pointer.
void Deck::takeFromDeck(Deck &otherDeck, int ID)
{
	if (m_myDeck.size() < 0)
		return;
	Card* tempCardPtr = m_myDeck[m_myDeck.size() - 1];
	m_myDeck.erase(m_myDeck.begin() + m_myDeck.size() - 1);//Delete last card.
	
	m_myDeck.push_back(tempCardPtr);
}

//Calculate the total of the cards.
//This is a separate function and not just a variable that iterates
//due to the ace being either 1 or 11
int Deck::calculateTotal() const
{
	return 10;//Not done yet.
}

//Might not be used as we may only ever move from deck to deck.
//Creates a new card out of nothingness
void Deck::addCard(int CID)
{
	//Can't use emplace_back because is a vector of pointers.
	m_myDeck.push_back(new Card(5, m_gamePtr));
}

int Deck::getCard(unsigned int ID) const
{
	if (ID>m_myDeck.size())
		return -1;
	return m_myDeck[ID]->getCardId();
}

const char* Deck::getCardName(unsigned int ID) const
{
	if (ID>m_myDeck.size() - 1)
		return "Card Doesn't Exist\0";
	return m_myDeck[ID]->getName();
}

int Deck::getCardAmount() const
{
	return m_myDeck.size();
}

//Will generate the main deck by getting 52 cards and randomizing the order.
void Deck::generateMainDeck()
{
	//Running into problems when not using pointer, possibly stack overflow??
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	//Figure it out!
	//----------------------------------------------------------------------------------------------------------------------------------------------------------

	//Clear this deck just in case.
	clearMyDeck();

	std::vector<Card*> tempDeck;//Don't need to delete, memory will be used.
	
	//Create the cards in order in the array.
	std::cout << "Creating main deck and generating cards..." << std::endl;
	for (int i = 0;i < 52; i++)
	{
		//Generate card image
		Resources::instance().renderCard(i);
		//Create card (Constructor will assign card image to its sprite, so must be done in this order)
		tempDeck.push_back(new Card(i, m_gamePtr));
		
	}
	std::cout << "Done!" << std::endl;

	//Inefficient way of sorting array.
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
