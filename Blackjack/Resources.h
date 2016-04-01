#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <vector> // seems SFML/Graphics.hpp has vector in it.

class Resources
{
public:
	Resources();
	~Resources();

	void loadTexture(const char*, const char*);
	void loadTexture(const sf::Texture& copyTexture, const char* TextureName);
	//void loadComplete();
	sf::Texture* findTexture(const char*);

	void renderCard(const int& CardID);

private:
	std::vector<sf::Texture*> TexResources;//use array because 52 cards in a deck.
	std::vector<char*> TexNames;//use array because 52 cards in a deck.

	sf::RenderTexture m_CardRenderer;
	sf::Texture m_Cards[52];//use array because 52 cards in a deck.

	//bool m_doneLoading;
};

