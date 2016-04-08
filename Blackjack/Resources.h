#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	Resources.h/ Resources.cpp class
		This class will act as a container that holds all the games resources:
		(fonts, textures/sprites, etc)
		It is a singleton so that anything can find a texture or add one.
*/

//Struct that holds formations of symbols for certain cards.
struct cardFormation
{
	std::vector<sf::Vector2i> coords;
	void addCoords(int Num1, int Num2)	//Adds a symbol position to the card formation.
	{
		coords.emplace_back(Num1, Num2);
	}
};

class Resources
{
public:
	void loadTexture(const char*, const char*);									//Function for loading texture from a file to resources.
	void loadTexture(const sf::Texture& copyTexture, const char* TextureName);	//Overloaded function for copying a texture to resources.
	void renderCard(const int& CardID);											//Function that renders a card using its card ID to a surface then copies it to the texture resources.
	void addToCardFormation(int CNum, int x_, int y_);							//Function to add a card formation.
	void copyCardFormation(int sourceNum, int destNum);							//Copies one card formation to another, to make things simpler.
	void destroy();																//Destroys the singleton.
	sf::Font& getFont();														//Returns the main game font.
	sf::Texture* findTexture(const char*, bool = true);							//Function for searching through textures using their names.
	static Resources& instance();												//Function for singleton access.
	~Resources();																//Destructor to clean up the resources.

private:
	std::vector<sf::Texture*> m_texResources;		//Array that holds pointers to textures.
	std::vector<char*> m_texNames;					//Array that holds the name of textures so that they can be found.
	sf::RenderTexture m_CardRenderer;				//A rendertexture to help with the creation of cards.
	sf::Texture m_Cards[52];						//use array because 52 cards in a deck.
	sf::Font m_cardFont;							//The font that cards will use (and maybe more)
	cardFormation m_cardFormations[10];				//Formations of symbols for cards 1 - 10 (10 cards)
	static Resources* m_thisInstance;				//Singleton instance
	Resources();									//Private constructor so it can only create itself.
	Resources(Resources& copyFrom);					//Declare explicit copy constructor.
	void operator=(Resources& ORes);				//Declare explicit copy assignment operator.
};

