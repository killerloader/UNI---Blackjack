#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <vector> // seems SFML/Graphics.hpp has vector in it.

class Resources
{
public:
	void loadTexture(const char*, const char*);
	void loadTexture(const sf::Texture& copyTexture, const char* TextureName);
	//void loadComplete();
	sf::Texture* findTexture(const char*);
	void renderCard(const int& CardID);

	static Resources& instance();//For singleton

	//~Resources();//Just create implicit version.
private:
	std::vector<sf::Texture*> TexResources;//use array because 52 cards in a deck.
	std::vector<char*> TexNames;//use array because 52 cards in a deck.

	sf::RenderTexture m_CardRenderer;
	sf::Texture m_Cards[52];//use array because 52 cards in a deck.

	static Resources* m_thisInstance;

	Resources();
	Resources(Resources& copyFrom);//Define copy constructor so that the implicit version isn't created in public. (Not sure if that actually happens)
	Resources& operator=(Resources& ORes_);

	//bool m_doneLoading;
};

