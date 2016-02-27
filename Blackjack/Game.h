#pragma once
#include <SFML/Graphics.hpp>


class Deck;

//Game class definition.
class Game
{
public:
	Game();
	~Game();

	void Run();
	void Draw();

	Deck* m_gameDeck;

	sf::RenderWindow m_window;
};

