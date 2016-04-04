#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Deck;

//Game class definition.
class Game
{
public:
	Game();
	~Game();

	void Run();
	void Draw();

	Deck* getGameDeck();

	//Resources m_gameResources;
private:
	Deck* m_gameDeck;

	sf::RenderWindow m_window;
};

