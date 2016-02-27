/*
------------------------------------------------------
	File Name: Game.cpp
	Author:	Heath Sargent
------------------------------------------------------
	Purpose:
	Create all game objects/ variables
	and run all game related code.
------------------------------------------------------
*/


#include "Game.h"

//Game class constructor
Game::Game()
{
	//Create classes
}

//Game class destructor
Game::~Game()
{
	//Destroy pointers
}

//Game run function, this will hold the game loop.
void Game::Run()
{
	//Creates a window/ OpenGL window context that will be used for displaying sprites. (Uses the declared window in Game class header)
	window.create(sf::VideoMode(640, 480), "Blackjack");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Draw();
	}

}

//A separate function for drawing, just to split up the main function.
void Game::Draw()
{
	//Clear screen to black (by default)
	window.clear();
	
	//Draw everything

	//Draw screen buffer now that everything has been drawn to it.
	window.display();
}