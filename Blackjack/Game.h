#pragma once
#include <SFML/Graphics.hpp>

//Game class definition.
class Game
{
public:
	Game();
	~Game();

	void Run();
	void Draw();

	sf::RenderWindow window;
};

