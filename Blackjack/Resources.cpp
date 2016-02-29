#include "Resources.h"

Resources::Resources()
{
	m_doneLoading = false;
	loadTexture("Data/Cards.jpg", "Cards");//String-literals don't go out of scope.
}

Resources::~Resources()
{

}

void Resources::loadComplete()
{
	m_doneLoading = true;
}

//Uses a RenderTexture / Surface to create cards and then save them as a normal texture.
void Resources::renderCard(int CardID)
{
	int CardType = (int)floor(CardID / 13);//Suit of card (0 = Clubs, 1 = Spades, 2 = Hearts, 3 = Diamonds)
}

void Resources::loadTexture(const char* FileName, const char* TextureName)
{
	/*
		If a texture is loaded after an object has called the findTexture() function
		its memory address can change, which makes the address that the function previously
		returned point to nothing.
		One solution to this is to disable the loading of textures in the constructor, so that
		none can be loaded after another class has gotten access to a pointer to a texture in the vector.
	*/
	if (m_doneLoading)
	{
		std::cout << "An attempt to load a texture after calling \"loadComplete()\" has been made." << std::endl;
		std::cout << "Ignoring texture load of: " << FileName << std::endl;
		return;
	}
	TexResources.emplace_back();
	TexResources[TexResources.size() - 1].loadFromFile(FileName);
	TexNames.push_back(TextureName);
}

sf::Texture* Resources::findTexture(const char* SearchName)
{
	if (!m_doneLoading)
	{
		std::cout << "An attempt to find a texture before calling \"loadComplete()\" has been made." << std::endl;
		std::cout << "\"loadComplete()\" must be called before a texture search!" << std::endl;
		std::cout << "Ignoring texture search: " << SearchName << std::endl;
		return nullptr;
	}
	for (unsigned int i = 0; i < TexNames.size(); i++)
		if (strcmp(SearchName, TexNames[i]) == 0)
			return &TexResources[i];
	std::cout << "Unable to find texture: " << SearchName << std::endl;
	return nullptr;
}