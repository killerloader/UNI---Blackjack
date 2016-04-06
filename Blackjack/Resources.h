#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <vector> // seems SFML/Graphics.hpp has vector in it.

/*
	Resources.h/ Resources.cpp class

		This will act as a handler for all of the game resources.
		Some of the functions in this class are specific to this program, as such this class
		does not use data abstraction entirely.
*/

struct cardFormation
{
	std::vector<int> coordsX;
	std::vector<int> coordsY;
	void addCoords(int Num1, int Num2)
	{
		coordsX.push_back(Num1);
		coordsY.push_back(Num2);
	}
};

class Resources
{
public:
	void loadTexture(const char*, const char*);
	void loadTexture(const sf::Texture& copyTexture, const char* TextureName);
	//void loadComplete();
	sf::Texture* findTexture(const char*);
	void renderCard(const int& CardID);

	void addToCardFormation(int CNum, int x_, int y_);

	static Resources& instance();//For singleton

	//~Resources();//Just create implicit version.
private:
	std::vector<sf::Texture*> TexResources;//use array because 52 cards in a deck.
	std::vector<char*> TexNames;//use array because 52 cards in a deck.

	sf::Font m_cardFont;

	cardFormation m_cardFormations[10];//Formations of symbols for cards 1 - 10 (10 cards)

	sf::RenderTexture m_CardRenderer;
	sf::Texture m_Cards[52];//use array because 52 cards in a deck.

	static Resources* m_thisInstance;

	Resources();
	Resources(Resources& copyFrom);//Define copy constructor so that the implicit version isn't created in public. (Not sure if that actually happens)
	Resources& operator=(Resources& ORes_);

	//bool m_doneLoading;
};

