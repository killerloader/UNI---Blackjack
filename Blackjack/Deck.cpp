#include "Deck.h"
#include "Card.h"
#include "Game.h"

#include <iostream>

//Deck constructor, takes a refernce to the main game project.
Deck::Deck(Game &gameRef) : m_gameRef(gameRef)
{
	//Setup cache for the total value of the deck.
	m_cachedTotal = 0;
	m_totalChanged = false;

	//Setup rectangle which shows the value of the deck.
	m_valueRect.setSize(sf::Vector2f(40, 20));
	m_valueRect.setFillColor(sf::Color(0, 0, 0, 150));

	//Sets up the value text in the rectangle.
	m_totalText.setFont(Resources::instance().getFont());
	m_totalText.setString("0");
	m_totalText.setCharacterSize(20);
}

Deck::~Deck()
{
	//Delete all cards in deck.
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		delete m_myDeck[i];
}

//TakeFromDeck() will take cards from another deck (removing them from the other deck and adding them to this deck)
//could also call this 'drawCard'
Card* Deck::takeFromDeck(Deck &otherDeck)
{
	//Other deck is empty, so can't take anything.
	if (otherDeck.m_myDeck.size() <= 0)
		return nullptr;

	//Create temporary copy of last card pointer for the other deck.
	Card* tempCardPtr = otherDeck.m_myDeck[otherDeck.m_myDeck.size() - 1];

	//Remove last card from other deck.
	otherDeck.m_myDeck.erase(otherDeck.m_myDeck.begin() + otherDeck.m_myDeck.size() - 1);

	//Add last card to this deck.
	m_myDeck.push_back(tempCardPtr);

	//The total has changed, so the value cache is invalid.
	m_totalChanged = true;
	otherDeck.m_totalChanged = true;

	return m_myDeck[m_myDeck.size() - 1];
}

//Calculate the total of the cards.
//This is a separate function and not just a variable that iterates
//due to the ace being either 1 or 11
//Not a const function due to the cache of the total needing to be changed.
int Deck::calculateTotal()
{
	if (!m_totalChanged)
		return m_cachedTotal;

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

	//Cache result.
	m_totalChanged = false;
	m_cachedTotal = totalValue;

	//Cache result into drawable text.
	char* totalBuffer = new char[4];//Max 3 digit number. (max value of a deck is ~350, although it wont go over 31 due to busting)
	sprintf_s(totalBuffer, 4, "%d", m_cachedTotal);
	m_totalText.setString(totalBuffer);

	delete[] totalBuffer;

	return m_cachedTotal;
}

//Might not be used as we may only ever move from deck to deck.
//Creates a new card out of nothingness
void Deck::addCard(int CID)
{
	//Can't use emplace_back because is a vector of pointers.
	m_myDeck.push_back(new Card(5, m_gameRef));

	//The total has changed, so the value cache is invalid.
	m_totalChanged = true;
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
void Deck::drawDeck(int x, int y, int sep)
{
	calculateTotal();

	//Draw each card in the deck.
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
	{
		m_myDeck[i]->getSprite().setPosition((float)x + i*sep, (float)y);
		m_gameRef.getWindow().draw(m_myDeck[i]->getSprite());
	}

	//Check if deck is not empty.
	if (m_myDeck.size() != 0)
	{
		//Draw the rectangle and the value of the card inside it.
		m_valueRect.setPosition((float)x - 44, (float)y);

		//Center text on button.
		m_totalText.setOrigin(m_totalText.getLocalBounds().left + m_totalText.getLocalBounds().width / 2, m_totalText.getLocalBounds().top + m_totalText.getLocalBounds().height / 2);
		m_totalText.setPosition(m_valueRect.getPosition().x + m_valueRect.getLocalBounds().width / 2, m_valueRect.getPosition().y + m_valueRect.getLocalBounds().height / 2);

		m_gameRef.getWindow().draw(m_valueRect);
		m_gameRef.getWindow().draw(m_totalText);
	}
}

//Gets the width of the deck (in drawn space) given a card separation value.
int Deck::getWidth(int separation)
{
	if (m_myDeck.size() == 0)
		return 0;
	int cardWidth = (int)m_myDeck[0]->getSprite().getLocalBounds().width;
	return cardWidth + separation*(m_myDeck.size()-1);
}


//Get the height of the deck (same as the height of one card, although if the deck is empty, this will be 0)
int Deck::getHeight()
{
	if (m_myDeck.size() == 0)
		return 0;
	return (int)m_myDeck[0]->getSprite().getLocalBounds().height;
}

//Will generate the main deck by getting 52 cards and randomizing the order.
void Deck::generateMainDeck()
{
	//Clear this deck just in case.
	clearDeck();
	
	//Create the cards in order in the array.
	std::cout << "Creating main deck and generating cards..." << std::endl;

	//Iterate through every card ID.
	for (int i = 0;i < 52; i++)
	{
		//Generate card image
		Resources::instance().renderCard(i);

		//Create card (Constructor will assign card image to its sprite, so must be done in this order)
		m_myDeck.push_back(new Card(i, m_gameRef));
	}

	std::cout << "Done!" << std::endl;

	//Shuffle the deck.
	shuffle();
}

//Shuffles the deck.
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

//Returns the amount of cards in the deck.
unsigned int Deck::getSize()
{
	return m_myDeck.size();
}

//Clears every card from the deck and deletes the cards.
void Deck::clearDeck()
{
	for (unsigned int i = 0; i < m_myDeck.size(); i++)
		delete m_myDeck[i];

	m_myDeck.clear();

	//Cached value of deck is now invalid.
	m_totalChanged = true;
}
