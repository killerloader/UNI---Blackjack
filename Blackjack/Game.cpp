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

#include <sstream>

#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Resources.h"

//Game class constructor with initializer list for Deck class object which needs to call its constructor.
Game::Game()
{
	//Setup symbol positions for cards.
	int midX = 34;
	int midY = 45;
	//A
	Resources::instance().addToCardFormation(0, midX, midY);
	//2
	Resources::instance().addToCardFormation(1, midX, 16);
	Resources::instance().addToCardFormation(1, midX, 74);
	//3
	Resources::instance().addToCardFormation(2, midX, 16);
	Resources::instance().addToCardFormation(2, midX, midY);
	Resources::instance().addToCardFormation(2, midX, 74);
	//4
	Resources::instance().addToCardFormation(3, 23, 16);
	Resources::instance().addToCardFormation(3, 23, 74);
	Resources::instance().addToCardFormation(3, 45, 16);
	Resources::instance().addToCardFormation(3, 45, 74);
	//5
	Resources::instance().addToCardFormation(4, 23, 16);
	Resources::instance().addToCardFormation(4, 23, 74);
	Resources::instance().addToCardFormation(4, midX, midY);
	Resources::instance().addToCardFormation(4, 45, 16);
	Resources::instance().addToCardFormation(4, 45, 74);
	//6
	Resources::instance().addToCardFormation(5, 23, 16);
	Resources::instance().addToCardFormation(5, 45, 16);
	Resources::instance().addToCardFormation(5, 23, midY);
	Resources::instance().addToCardFormation(5, 45, midY);
	Resources::instance().addToCardFormation(5, 23, 74);
	Resources::instance().addToCardFormation(5, 45, 74);
	//7
	Resources::instance().addToCardFormation(6, 23, 16);
	Resources::instance().addToCardFormation(6, 45, 16);
	Resources::instance().addToCardFormation(6, midX, 31);//14 above midy
	Resources::instance().addToCardFormation(6, 23, midY);
	Resources::instance().addToCardFormation(6, 45, midY);
	Resources::instance().addToCardFormation(6, 23, 74);
	Resources::instance().addToCardFormation(6, 45, 74);
	//8
	Resources::instance().addToCardFormation(7, 23, 16);
	Resources::instance().addToCardFormation(7, 45, 16);
	Resources::instance().addToCardFormation(7, midX, 31);//14 above midy
	Resources::instance().addToCardFormation(7, 23, midY);
	Resources::instance().addToCardFormation(7, 45, midY);
	Resources::instance().addToCardFormation(7, midX, 59);//14 below midy
	Resources::instance().addToCardFormation(7, 23, 74);
	Resources::instance().addToCardFormation(7, 45, 74);
	//9
	Resources::instance().addToCardFormation(8, 23, 16);
	Resources::instance().addToCardFormation(8, 45, 16);

	Resources::instance().addToCardFormation(8, 23, 35);
	Resources::instance().addToCardFormation(8, 45, 35);

	Resources::instance().addToCardFormation(8, midX, midY);

	Resources::instance().addToCardFormation(8, 23, 55);
	Resources::instance().addToCardFormation(8, 45, 55);

	Resources::instance().addToCardFormation(8, 23, 74);
	Resources::instance().addToCardFormation(8, 45, 74);

	//10
	Resources::instance().addToCardFormation(9, 23, 16);
	Resources::instance().addToCardFormation(9, 45, 16);
											 
	Resources::instance().addToCardFormation(9, 23, 35);
	Resources::instance().addToCardFormation(9, 45, 35);
											 
	Resources::instance().addToCardFormation(9, midX, 25);
	Resources::instance().addToCardFormation(9, midX, 65);
											 
	Resources::instance().addToCardFormation(9, 23, 55);
	Resources::instance().addToCardFormation(9, 45, 55);
											 
	Resources::instance().addToCardFormation(9, 23, 74);
	Resources::instance().addToCardFormation(9, 45, 74);


	//Render cards
	for (int i = 0; i < 52; i++)
		Resources::instance().renderCard(i);

	//Create class pointers
	m_gameDeck = new Deck(this);
	m_gameDeck->generateMainDeck();
	//testDeck->takeFromDeck(*m_gameDeck);
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

	sf::Sprite test(*Resources::instance().findTexture("Card:33"));
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			std::stringstream myStream;
			myStream << "Card:" << rand() % 52;
			std::cout << "Card changed to: " << myStream.str() << std::endl;
			test.setTexture(*Resources::instance().findTexture(myStream.str().c_str()));
		}

		m_window.draw(test);

		//Draw screen buffer now that everything has been drawn to it.
		m_window.display();
	}
}

//A separate function for drawing, just to split up the main function.
void Game::Draw()
{
	
}

Deck* Game::getGameDeck()
{
	return m_gameDeck;
}