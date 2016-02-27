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
#include "Deck.h"

//Game class constructor with initializer list for Deck class object which needs to call its constructor.
Game::Game()
{
	//Create class pointers
	m_gameDeck = new Deck(1);
}

//Game class destructor
Game::~Game()
{
	//Destroy pointers
	delete m_gameDeck;
}

//Game run function, this will hold the game loop.
void Game::Run()
{
	//Creates a window that will be used for displaying sprites.
	m_window.create(sf::VideoMode(640, 480), "Blackjack");

	//Game loop
	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		//Clear screen to black (by default)
		m_window.clear();

		//Actually draw stuff.
		Draw();

		//Draw screen buffer now that everything has been drawn to it.
		m_window.display();
	}
}

//A separate function for drawing, just to split up the main function.
void Game::Draw()
{
	
}