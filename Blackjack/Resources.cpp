#include "Resources.h"
#include <sstream>

Resources* Resources::m_thisInstance = nullptr;

Resources::Resources()
{
	//m_doneLoading = false;
	loadTexture("Data/Cards.jpg", "Cards");//String-literals don't go out of scope.
	loadTexture("Data/CardOutput/CardBackground.png", "CardBackground");
	loadTexture("Data/CardOutput/HeartBig.png", "HeartBig");
	loadTexture("Data/CardOutput/HeartSmall.png", "HeartSmall");
	loadTexture("Data/CardOutput/DiamondBig.png", "DiamondBig");
	loadTexture("Data/CardOutput/DiamondSmall.png", "DiamondSmall");

	m_cardFont.loadFromFile("Data/micross.ttf");
}

Resources::Resources(Resources& copyFrom)
{
	//Not actually used, only here to define private copy constructor so nothing can copy it.
	//Makes it non-copyable.
}

Resources& Resources::operator=(Resources& ORes_)
{
	//Not actually used, only here to define private copy asignment opererator overload so nothing can copy it.
	//Makes it non-copyable.
}

Resources& Resources::instance()
{
	if (m_thisInstance == nullptr)
		m_thisInstance = new Resources();
	return *m_thisInstance;
}

//Uses a RenderTexture / Surface to create cards and then save them as a normal texture.
//Function should probably be in game, and not in Resources.
void Resources::renderCard(const int& CardID)
{
	//int CardType = CardID / 13;//Suit of card (0 = Clubs, 1 = Spades, 2 = Hearts, 3 = Diamonds)

	sf::RenderTexture tempRenderTexture;
	tempRenderTexture.create(67, 91);//64 x 90 is the size of the cards.
	sf::Sprite tempSpr(*findTexture("CardBackground"));
	sf::Sprite cardSuitBig_, cardSuitSmall_;

	//Setup sprite offsets for small suit image.
	int setSuitSmallOffset[4][2]{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };//Offset for the sprites for each set, based on diamond location.
	setSuitSmallOffset[0][0] = 0; setSuitSmallOffset[0][1] = 0;
	setSuitSmallOffset[1][0] = 0; setSuitSmallOffset[1][1] = 0;
	setSuitSmallOffset[2][0] = -1; setSuitSmallOffset[2][1] = 1;//Hearts
	//DiamondBig

	int suit_ = CardID / 13;//Will truncate towards 0.
	int cardNum = CardID - suit_ * 13;
	char* cardSymbol;

	//Alternatively just create an array of symbols and point the cardNum to that.
	switch (cardNum)
	{
	case 0:cardSymbol = new char[2]{ 'A' }; break;
	case 1:cardSymbol = new char[2]{ '2' }; break;
	case 2:cardSymbol = new char[2]{ '3' }; break;
	case 3:cardSymbol = new char[2]{ '4' }; break;
	case 4:cardSymbol = new char[2]{ '5' }; break;
	case 5:cardSymbol = new char[2]{ '6' }; break;
	case 6:cardSymbol = new char[2]{ '7' }; break;
	case 7:cardSymbol = new char[2]{ '8' }; break;
	case 8:cardSymbol = new char[2]{ '9' }; break;
	case 9:cardSymbol = new char[3]{ "10" }; break;
	case 10:cardSymbol = new char[2]{ 'J' }; break;
	case 11:cardSymbol = new char[2]{ 'K' }; break;
	case 12:cardSymbol = new char[2]{ 'Q' }; break;
	default:cardSymbol = new char[2]{ 'E' }; break;
	}

	switch (suit_)
	{
	case 2://Hearts
		cardSuitBig_.setTexture(*findTexture("HeartBig"));
		cardSuitSmall_.setTexture(*findTexture("HeartSmall"));
		break;
	case 3://diamonds
		cardSuitBig_.setTexture(*findTexture("DiamondBig"));
		cardSuitSmall_.setTexture(*findTexture("DiamondSmall"));
		break;
	default://ERROR/ None
		cardSuitBig_.setTexture(*findTexture("DiamondBig"));
		cardSuitSmall_.setTexture(*findTexture("DiamondSmall"));
		break;
	}
	cardSuitBig_.setOrigin((cardSuitBig_.getLocalBounds().width + 1) / 2, (cardSuitBig_.getLocalBounds().height + 1) / 2);//Will truncate down
	cardSuitSmall_.setOrigin((cardSuitSmall_.getLocalBounds().width+1) / 2, (cardSuitSmall_.getLocalBounds().height + 1) / 2);//Will truncate down

	tempRenderTexture.clear();
	//Draw the base of the card.
	tempRenderTexture.draw(tempSpr);

	//We have less space with Q J and K, so give separate coords for the items on both cases.
	int BorderItemPos[2]{ 6, 61 };
	if (cardNum < 10)//Not J K or Q
	{
		BorderItemPos[0] = 8;
		BorderItemPos[1] = 59;

		//Draw large symbols.
		for (int i = 0; i < m_cardFormations[cardNum].coordsX.size(); i++)
		{
			cardSuitBig_.setPosition(m_cardFormations[cardNum].coordsX[i], m_cardFormations[cardNum].coordsY[i]);
			if (m_cardFormations[cardNum].coordsY[i]>45)//Past half way
				cardSuitBig_.setScale(1, -1);//Flip
			else
				cardSuitBig_.setScale(1, 1);//Default
			tempRenderTexture.draw(cardSuitBig_);
		}
	}

	//Draw top left suit.
	cardSuitSmall_.setPosition(BorderItemPos[0], 23);
	tempRenderTexture.draw(cardSuitSmall_);
	//Draw bottom right suit.
	cardSuitSmall_.setPosition(BorderItemPos[1], 65);
	cardSuitSmall_.setScale(-1,-1);
	tempRenderTexture.draw(cardSuitSmall_);
	//

	sf::Text cardNumberString(cardSymbol, m_cardFont, 13);
	cardNumberString.setStyle(sf::Text::Bold);
	//cardNumberString.set
	cardNumberString.setOrigin((cardNumberString.getLocalBounds().width+1) / 2, (cardNumberString.getLocalBounds().height+1) / 2);
	cardNumberString.setPosition(BorderItemPos[0], 8);
	cardNumberString.setColor(sf::Color::Black);
	tempRenderTexture.draw(cardNumberString);
	cardNumberString.setPosition(BorderItemPos[1], 81);
	cardNumberString.setScale(-1,-1);
	tempRenderTexture.draw(cardNumberString);
	

	tempRenderTexture.display();

	std::stringstream tempStream;
	tempStream << "Card:" << CardID;

	loadTexture(tempRenderTexture.getTexture(), tempStream.str().c_str());
}

void Resources::addToCardFormation(int CNum, int x_, int y_)
{
	if (CNum < 0)
		return;
	if (CNum > 9)
		return;
	m_cardFormations[CNum].addCoords(x_, y_);
}

void Resources::loadTexture(const char* FileName, const char* TextureName)
{
	/*
	If a texture is loaded after an object has called the findTexture() function
	its memory address can change, which makes the address that the function previously
	returned point to nothing.
	One solution to this is to disable the loading of textures in the constructor, so that
	none can be loaded after another class has gotten access to a pointer to a texture in the vector.
	Or just hold a vector of pointers.
	*/

	TexResources.push_back(new sf::Texture);
	TexResources[TexResources.size() - 1]->loadFromFile(FileName);
	TexNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(TexNames[TexNames.size() - 1], strlen(TextureName) + 1, TextureName);
}

void Resources::loadTexture(const sf::Texture& copyTexture, const char* TextureName)
{
	TexResources.push_back(new sf::Texture(copyTexture));
	TexNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(TexNames[TexNames.size() - 1], strlen(TextureName) + 1, TextureName);
}

sf::Texture* Resources::findTexture(const char* SearchName)
{
	for (unsigned int i = 0; i < TexNames.size(); i++)
		if (strcmp(SearchName, TexNames[i]) == 0)
			return TexResources[i];
	std::cout << "Unable to find texture: " << SearchName << std::endl;
	return nullptr;
}