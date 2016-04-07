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
	//Setup the symbol positions for the cards when they get rendered.
	setupSymbolPositions();

	//Create class pointers
	m_gameDeck = new Deck(this);
	//Generate the main deck, creates all 52 cards in order then shuffles them.
	m_gameDeck->generateMainDeck();
	//testDeck->takeFromDeck(*m_gameDeck);
}

//Game class destructor
Game::~Game()
{
	//Destroy pointers
	delete m_gameDeck;
}

void Game::setupSymbolPositions()
{
	//Setup symbol positions for cards.
	int midX = 33;
	int leftX = midX - 11;//11 left of mid
	int rightX = midX + 11;//11 right of mid
	int midY = 45;
	int topY = midY - 29;//29 above mid
	int bottomY = midY + 29;//29 below mid
	


	//A
	Resources::instance().addToCardFormation(0, midX, midY);
	//2
	Resources::instance().addToCardFormation(1, midX, topY);
	Resources::instance().addToCardFormation(1, midX, 74);
	//3
	Resources::instance().addToCardFormation(2, midX, topY);
	Resources::instance().addToCardFormation(2, midX, midY);
	Resources::instance().addToCardFormation(2, midX, bottomY);
	//4
	Resources::instance().addToCardFormation(3, leftX, topY);
	Resources::instance().addToCardFormation(3, leftX, bottomY);
	Resources::instance().addToCardFormation(3, midX+11, topY);
	Resources::instance().addToCardFormation(3, midX+11, bottomY);
	//5
	Resources::instance().addToCardFormation(4, leftX, topY);
	Resources::instance().addToCardFormation(4, leftX, bottomY);
	Resources::instance().addToCardFormation(4, midX, midY);
	Resources::instance().addToCardFormation(4, rightX, topY);
	Resources::instance().addToCardFormation(4, rightX, bottomY);
	//6
	Resources::instance().addToCardFormation(5, leftX, topY);
	Resources::instance().addToCardFormation(5, rightX, topY);
	Resources::instance().addToCardFormation(5, leftX, midY);
	Resources::instance().addToCardFormation(5, rightX, midY);
	Resources::instance().addToCardFormation(5, leftX, bottomY);
	Resources::instance().addToCardFormation(5, 45, bottomY);
	//7
	Resources::instance().addToCardFormation(6, leftX, topY);
	Resources::instance().addToCardFormation(6, rightX, topY);
	Resources::instance().addToCardFormation(6, midX, 31);//14 above midy
	Resources::instance().addToCardFormation(6, leftX, midY);
	Resources::instance().addToCardFormation(6, rightX, midY);
	Resources::instance().addToCardFormation(6, leftX, bottomY);
	Resources::instance().addToCardFormation(6, rightX, 74);
	//8
	Resources::instance().addToCardFormation(7, leftX, topY);
	Resources::instance().addToCardFormation(7, rightX, topY);
	Resources::instance().addToCardFormation(7, midX, 31);//14 above midy
	Resources::instance().addToCardFormation(7, leftX, midY);
	Resources::instance().addToCardFormation(7, rightX, midY);
	Resources::instance().addToCardFormation(7, midX, 59);//14 below midy
	Resources::instance().addToCardFormation(7, leftX, 74);
	Resources::instance().addToCardFormation(7, rightX, 74);
	//9
	Resources::instance().addToCardFormation(8, leftX, topY);
	Resources::instance().addToCardFormation(8, rightX, topY);

	Resources::instance().addToCardFormation(8, leftX, 35);
	Resources::instance().addToCardFormation(8, rightX, 35);

	Resources::instance().addToCardFormation(8, midX, midY);

	Resources::instance().addToCardFormation(8, leftX, 55);
	Resources::instance().addToCardFormation(8, rightX, 55);

	Resources::instance().addToCardFormation(8, leftX, 74);
	Resources::instance().addToCardFormation(8, rightX, 74);

	//10
	Resources::instance().addToCardFormation(9, leftX, topY);
	Resources::instance().addToCardFormation(9, rightX, topY);

	Resources::instance().addToCardFormation(9, leftX, 35);
	Resources::instance().addToCardFormation(9, rightX, 35);

	Resources::instance().addToCardFormation(9, midX, 25);
	Resources::instance().addToCardFormation(9, midX, 65);

	Resources::instance().addToCardFormation(9, leftX, 55);
	Resources::instance().addToCardFormation(9, rightX, 55);

	Resources::instance().addToCardFormation(9, leftX, 74);
	Resources::instance().addToCardFormation(9, rightX, 74);
}

//Game run function, this will hold the game loop.
void Game::Run()
{
	//Creates a window that will be used for displaying sprites.
	m_window.create(sf::VideoMode(640, 480), "Blackjack");
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);

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