#include "Resources.h"
#include <sstream>

Resources* Resources::m_thisInstance = nullptr;

Resources::Resources()
{
	//m_doneLoading = false;
	loadTexture("Data/Cards.jpg", "Cards");//String-literals don't go out of scope.
	loadTexture("Data/CardOutput/CardBackground.png", "cardBackground");//String-literals don't go out of scope.
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

/*Resources::~Resources()
{

}*/

Resources& Resources::instance()
{
	if (m_thisInstance == nullptr)
		m_thisInstance = new Resources();
	return *m_thisInstance;
}

/*void Resources::loadComplete()
{
	m_doneLoading = true;
}*/

//Uses a RenderTexture / Surface to create cards and then save them as a normal texture.
//Function should probably be in game, and not in Resources.
void Resources::renderCard(const int& CardID)
{
	//int CardType = CardID / 13;//Suit of card (0 = Clubs, 1 = Spades, 2 = Hearts, 3 = Diamonds)

	sf::RenderTexture tempRenderTexture;
	tempRenderTexture.create(64, 90);//64 x 90 is the size of the cards.
	sf::Sprite tempSpr(*findTexture("cardBackground"));

	tempRenderTexture.clear();
	tempRenderTexture.draw(tempSpr);
	tempRenderTexture.display();

	std::stringstream tempStream;
	tempStream << "Card:" << CardID;

	loadTexture(tempRenderTexture.getTexture(), tempStream.str().c_str());
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
	/*if (m_doneLoading)
	{
	std::cout << "An attempt to load a texture after calling \"loadComplete()\" has been made." << std::endl;
	std::cout << "Ignoring texture load of: " << FileName << std::endl;
	return;
	}*/

	TexResources.push_back(new sf::Texture);
	TexResources[TexResources.size() - 1]->loadFromFile(FileName);
	TexNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(TexNames[TexNames.size() - 1], strlen(TextureName) + 1, TextureName);
	//TexNames.push_back(TextureName);
}

void Resources::loadTexture(const sf::Texture& copyTexture, const char* TextureName)
{
	TexResources.push_back(new sf::Texture(copyTexture));
	TexNames.push_back(new char[strlen(TextureName) + 1]);
	strcpy_s(TexNames[TexNames.size() - 1], strlen(TextureName) + 1, TextureName);
	//TexNames.push_back(TextureName);
}

sf::Texture* Resources::findTexture(const char* SearchName)
{
	/*if (!m_doneLoading)
	{
		std::cout << "An attempt to find a texture before calling \"loadComplete()\" has been made." << std::endl;
		std::cout << "\"loadComplete()\" must be called before a texture search!" << std::endl;
		std::cout << "Ignoring texture search: " << SearchName << std::endl;
		return nullptr;
	}*/
	for (unsigned int i = 0; i < TexNames.size(); i++)
		if (strcmp(SearchName, TexNames[i]) == 0)
			return TexResources[i];
	std::cout << "Unable to find texture: " << SearchName << std::endl;
	return nullptr;
}