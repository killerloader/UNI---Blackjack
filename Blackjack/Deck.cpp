#include "Deck.h"
#include "Card.h"
#include <iostream>

Deck::Deck()
{

}

Deck::~Deck()
{

}

//TakeFromDeck() will take cards from another deck (removing them from the other deck and adding them to this deck)
//If ID is left as -1, it will take the last card from the deck.
//otherwise it will take the card at the index "ID" in the vector.
//could also call this 'drawCard'
void Deck::takeFromDeck(Deck &otherDeck, int ID)
{
	//Take card from other deck and add it to own with a pointer.
	m_myDeck.push_back(otherDeck.takeCard());
}

//Calculate the total of the cards.
//This is a separate function and not just a variable that iterates
//due to the ace being either 1 or 11
int Deck::calculateTotal()
{
	return 10;//Not done yet.
}

//Might not be used as we may only ever move from deck to deck.
void Deck::addCard(Card*)
{
	//Probably only e
}

//Will remove a card from this deck and return a pointer to its memory.
//If this is used the in wrong place, the memory of the card will never get deleted.
Card* Deck::takeCard()
{
	if (m_myDeck.size() < 0)
		return nullptr;
	Card* tempCardPtr= m_myDeck[m_myDeck.size() - 1];
	//Here
	m_myDeck.erase(m_myDeck.begin() + m_myDeck.size() - 1);//Delete last card.
	return tempCardPtr;
}

int Deck::getCard(int ID)
{
	if (ID<0 || ID>m_myDeck.size())
		return -1;
	return m_myDeck[ID]->getCardId();
}

const char* Deck::getCardName(int ID)
{
	if (ID<0 || ID>m_myDeck.size() - 1)
		return "Card Doesn't Exist\0";
	return m_myDeck[ID]->getName();
}

int Deck::getCardAmount()
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
	std::vector<Card*> tempDeck;//Don't need to delete, memory will be used.
	
	//Create the cards in order in the array.
	for (int i = 0;i < 52; i++)
	{
		//c++ 11 function to call constructor on what is emplaced back, avoids copies.
		tempDeck.push_back(new Card(i));
	}

	clearMyDeck();

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
