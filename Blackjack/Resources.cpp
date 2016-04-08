#include "Resources.h"

#include <sstream>

//Set singleton instance to nullptr.
Resources* Resources::m_thisInstance = nullptr;

//Constructor, loads some textures which will be required later on
//Although this should actualy be done in the Game class if this were to use abstraction.
Resources::Resources()
{
	//String literals don't go out of scope.
	//Basically load card components for use with creating cards.
	loadTexture("Data/InnerCardOutline.png", "InnerOutline");//Outline for Jack, Queen and King image.
	loadTexture("Data/CardBackground.png", "CardBackground");
	loadTexture("Data/HeartBig.png", "HeartBig");
	loadTexture("Data/HeartSmall.png", "HeartSmall");
	loadTexture("Data/DiamondBig.png", "DiamondBig");
	loadTexture("Data/DiamondSmall.png", "DiamondSmall");
	loadTexture("Data/SpadeBig.png", "SpadeBig");
	loadTexture("Data/SpadeSmall.png", "SpadeSmall");
	loadTexture("Data/ClubBig.png", "ClubBig");
	loadTexture("Data/ClubSmall.png", "ClubSmall");
	loadTexture("Data/Jack.png", "JackImage");
	loadTexture("Data/Queen.png", "QueenImage");
	loadTexture("Data/King.png", "KingImage");

	//load main font (a windows default font)
	m_cardFont.loadFromFile("Data/micross.ttf");

	//Create card renderer rendertexture at start so it doesn't have to be created many times.
	m_CardRenderer.create(67, 91);
}

//Function to destroy the singleton and call its destructor.
void Resources::destroy()
{
	delete this;				//Delete self and call destructor.
	m_thisInstance = nullptr;	//Set static singleton instance to nullptr.
}

//Clean up game resources.
Resources::~Resources()
{
	//Delete each texture.
	for (unsigned int i = 0; i < m_texResources.size(); i++)
		delete m_texResources[i];

	//Delete each texture name.
	for (unsigned int i = 0; i < m_texNames.size(); i++)
		delete[] m_texNames[i];
}

//Removes public implicit copy constructor.
Resources::Resources(Resources& copyFrom) {};

//Removes public implicit copy assignment operator.
void Resources::operator=(Resources& ORes_) {};

//Singleton access.
Resources& Resources::instance()
{
	if (m_thisInstance == nullptr)
		m_thisInstance = new Resources();
	return *m_thisInstance;
}

sf::Font& Resources::getFont()
{
	return m_cardFont;
}

//Uses a RenderTexture / Surface to generate card sprites and then saves them as a normal resource.
//Function is more suited to be in Game class if this class were to use abstraction.
void Resources::renderCard(const int& CardID)
{
	//Get name of texture, to check if already created and to save at the end of the function if it is not.
	std::stringstream tempStream;
	tempStream << "Card:" << CardID;

	//Check if texture already exists. (and don't show errors)
	if (findTexture(tempStream.str().c_str(), false) != nullptr)
		return;

	//Clear the rendertexture so it can be used with a new card.
	m_CardRenderer.clear(sf::Color(255,255,255,0));
	sf::Sprite tempSpr(*findTexture("CardBackground"));
	sf::Sprite cardSuitBig, cardSuitSmall;

	//Setup card data.
	int suit_ = CardID / 13;//Will truncate towards 0.
	int cardNum = CardID - suit_ * 13;
	char* cardSymbol;//No point in setting to nullptr.

	//Get Number/ Letter of card in char array format to draw to card.
	//Alternatively just create an array of symbols and point the cardNum to that.
	//This probably gets optimized by the compiler anyways.
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
	case 11:cardSymbol = new char[2]{ 'Q' }; break;
	case 12:cardSymbol = new char[2]{ 'K' }; break;
	default:cardSymbol = new char[2]{ 'E' }; break;
	}

	//Set suit symbols according to suit of card.
	switch (suit_)
	{
	case 0://Clubs
		cardSuitBig.setTexture(*findTexture("ClubBig"));
		cardSuitSmall.setTexture(*findTexture("ClubSmall"));
		break;
	case 1://Spades
		cardSuitBig.setTexture(*findTexture("SpadeBig"));
		cardSuitSmall.setTexture(*findTexture("SpadeSmall"));
		break;
	case 2://Hearts
		cardSuitBig.setTexture(*findTexture("HeartBig"));
		cardSuitSmall.setTexture(*findTexture("HeartSmall"));
		break;
	case 3://diamonds
		cardSuitBig.setTexture(*findTexture("DiamondBig"));
		cardSuitSmall.setTexture(*findTexture("DiamondSmall"));
		break;
	default://ERROR/ None
		break;
	}

	//Set origin of suit symbols to their center so they can be more easily placed and scaled.
	cardSuitBig.setOrigin((cardSuitBig.getLocalBounds().width - 1) / 2, (cardSuitBig.getLocalBounds().height - 1) / 2);
	cardSuitSmall.setOrigin((cardSuitSmall.getLocalBounds().width - 1) / 2, (cardSuitSmall.getLocalBounds().height - 1) / 2);

	//Clear the render texture/ buffer (as you would clear the screen)
	m_CardRenderer.clear();

	//Draw the base of the card, just a blank canvas.
	//Blend mode "None" so that the transparency of the corners are kept.
	m_CardRenderer.draw(tempSpr, sf::BlendNone);

	//We have less space with Q J and K due to their image, so give separate coordinates for them.
	int borderItemPos[2]{ 6, 61 };//Initiate with 

	if (cardNum < 10)//Not a Jack, Queen or King
	{
		borderItemPos[0] = 8;
		borderItemPos[1] = 59;

		//Draw large symbols.
		for (unsigned int i = 0; i < m_cardFormations[cardNum].coords.size(); i++)
		{
			cardSuitBig.setPosition((float)m_cardFormations[cardNum].coords[i].x, (float)m_cardFormations[cardNum].coords[i].y);

			//If symbol position is past half way, flip it.
			if (m_cardFormations[cardNum].coords[i].y>45)
				cardSuitBig.setScale(1, -1);//Flip
			else
				cardSuitBig.setScale(1, 1);//Default

			m_CardRenderer.draw(cardSuitBig);
		}
	}
	else//Is a Jack, Queen or King
	{
		//Draw the inner outline which contains the card image.
		sf::Sprite innerOutlineSpr(*findTexture("InnerOutline"));

		//Set its position using int literals.
		innerOutlineSpr.setPosition(12, 11);
		m_CardRenderer.draw(innerOutlineSpr);

		//Select the appropriate image for the appropriate card.
		sf::Sprite innerCardImage;
		switch (cardNum)
		{
		case 10://Jack
			innerCardImage.setTexture(*findTexture("JackImage")); break;
		case 11://Queen
			innerCardImage.setTexture(*findTexture("QueenImage")); break;
		case 12://King
			innerCardImage.setTexture(*findTexture("KingImage")); break;
		}
		//Draw the image inside the inner outline.
		innerCardImage.setPosition(13, 12);
		m_CardRenderer.draw(innerCardImage);

		//Kings are flipped, so we draw the inner suit symbols on opposite ends.
		if (cardNum == 12)
		{
			//Draw top inner small suit.
			cardSuitSmall.setPosition(19.f, 20.f);
			m_CardRenderer.draw(cardSuitSmall);

			//Draw bottom inner small suit.
			cardSuitSmall.setPosition(47.f, 70.f);
			cardSuitSmall.setScale(1, -1);
			m_CardRenderer.draw(cardSuitSmall);
		}
		else//Not a king
		{
			//Draw top inner small suit.
			cardSuitSmall.setPosition(47.f, 20.f);
			m_CardRenderer.draw(cardSuitSmall);

			//Draw bottom inner small suit.
			cardSuitSmall.setPosition(19.f, 70.f);
			cardSuitSmall.setScale(1, -1);
			m_CardRenderer.draw(cardSuitSmall);
		}

		//Reset scale, as it gets used later.
		cardSuitSmall.setScale(1, 1);
	}

	//Draw top left small suit.
	cardSuitSmall.setPosition((float)borderItemPos[0], 23.f);
	m_CardRenderer.draw(cardSuitSmall);

	//Draw bottom right small suit.
	cardSuitSmall.setPosition((float)borderItemPos[1], 68.f);
	cardSuitSmall.setScale(-1,-1);
	m_CardRenderer.draw(cardSuitSmall);

	//Setup and draw the number/letter associated with the card.
	sf::Text cardNumberString(cardSymbol, m_cardFont, 13);
	cardNumberString.setColor(sf::Color::Black);
	if(suit_ == 2 || suit_ == 3)//red suit
		cardNumberString.setColor(sf::Color::Red);
	cardNumberString.setStyle(sf::Text::Bold);
	cardNumberString.setOrigin((cardNumberString.getLocalBounds().width-1) / 2, (cardNumberString.getLocalBounds().height-1) / 2);
	cardNumberString.setPosition((float)borderItemPos[0], 8.f);
	
	m_CardRenderer.draw(cardNumberString);
	cardNumberString.setPosition((float)borderItemPos[1], 83.f);
	cardNumberString.setScale(-1,-1);
	m_CardRenderer.draw(cardNumberString);

	//Display the temportary render texture, as it is ready to be used.
	m_CardRenderer.display();

	//Save this new sprite as a texture resource. Use stringstream to create its assigned name.
	loadTexture(m_CardRenderer.getTexture(), tempStream.str().c_str());

	//Delete temporary cardSymbol variable.
	delete[] cardSymbol;
}

//Adds a card to the symbol formations (cards A to 10)
void Resources::addToCardFormation(int CNum, int x_, int y_)
{
	if (CNum < 0 || CNum > 9)//not within A to 10
		return;

	m_cardFormations[CNum].addCoords(x_, y_);
}

//Copies one formation to another (as some formations are similar)
void Resources::copyCardFormation(int sourceNum, int destNum)
{
	if (sourceNum < 0 || sourceNum > 9 || destNum < 0 || destNum > 9)//not within A to 10
		return;

	for (unsigned int i = 0; i < m_cardFormations[sourceNum].coords.size(); i++)
		m_cardFormations[destNum].addCoords(m_cardFormations[sourceNum].coords[i].x, m_cardFormations[sourceNum].coords[i].y);
}

//Gets a texture from a file, and adds it to the resources.
void Resources::loadTexture(const char* FileName, const char* TextureName)
{
	m_texResources.push_back(new sf::Texture);
	m_texResources[m_texResources.size() - 1]->loadFromFile(FileName);
	m_texNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(m_texNames[m_texNames.size() - 1], strlen(TextureName) + 1, TextureName);
}

//Copies a texture and adds it to the resources.
void Resources::loadTexture(const sf::Texture& copyTexture, const char* TextureName)
{
	m_texResources.push_back(new sf::Texture(copyTexture));
	m_texNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(m_texNames[m_texNames.size() - 1], strlen(TextureName) + 1, TextureName);
}

//Searches for a texture using a name.
sf::Texture* Resources::findTexture(const char* SearchName, bool showError)
{
	for (unsigned int i = 0; i < m_texNames.size(); i++)
		if (strcmp(SearchName, m_texNames[i]) == 0)
			return m_texResources[i];

	if(showError)
		std::cout << "Unable to find texture: " << SearchName << std::endl;
	return nullptr;
}