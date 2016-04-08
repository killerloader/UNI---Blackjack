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
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Resources.h"
#include "GameButton.h"

//Game class constructor with initializer list for Deck class object which needs to call its constructor.
Game::Game()
{
	//Setup the symbol positions for the cards when they get rendered.
	setupSymbolPositions();

	//Create class pointers
	m_gameDeck = new Deck(*this);

	//Generate the main deck, creates all 52 cards in order then shuffles them.
	m_gameDeck->generateMainDeck();

	playerObj = new Player(*this);
	dealerObj = new Dealer(*this);

	hitButton = new GameButton(*this, 260,430,64,25, "Hit", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	standButton = new GameButton(*this, 380, 430, 64, 25, "Stand", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
}

//Game class destructor
Game::~Game()
{
	//Destroy pointers
	delete m_gameDeck;
	delete playerObj;
	delete dealerObj;
	delete hitButton;
	delete standButton;
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
	Resources::instance().copyCardFormation(0, 2);
	Resources::instance().copyCardFormation(1, 2);
	//4
	Resources::instance().addToCardFormation(3, leftX, topY);
	Resources::instance().addToCardFormation(3, leftX, bottomY);
	Resources::instance().addToCardFormation(3, midX+11, topY);
	Resources::instance().addToCardFormation(3, midX+11, bottomY);
	//5
	Resources::instance().copyCardFormation(0, 4);
	Resources::instance().copyCardFormation(3, 4);
	//6
	Resources::instance().copyCardFormation(3, 5);
	Resources::instance().addToCardFormation(5, leftX, midY);
	Resources::instance().addToCardFormation(5, rightX, midY);
	//7
	Resources::instance().copyCardFormation(5, 6);
	Resources::instance().addToCardFormation(6, midX, 31);//14 above midy
	//8
	Resources::instance().copyCardFormation(6, 7);
	Resources::instance().addToCardFormation(7, midX, 59);//14 below midy
	//9
	Resources::instance().copyCardFormation(4, 8);
	Resources::instance().addToCardFormation(8, leftX, 35);
	Resources::instance().addToCardFormation(8, rightX, 35);
	Resources::instance().addToCardFormation(8, leftX, 55);
	Resources::instance().addToCardFormation(8, rightX, 55);
	//10
	Resources::instance().copyCardFormation(3, 9);
	Resources::instance().addToCardFormation(9, leftX, 35);
	Resources::instance().addToCardFormation(9, rightX, 35);
	Resources::instance().addToCardFormation(9, midX, 25);
	Resources::instance().addToCardFormation(9, midX, 65);
	Resources::instance().addToCardFormation(9, leftX, 55);
	Resources::instance().addToCardFormation(9, rightX, 55);
}

//Game run function, this will hold the game loop.
void Game::Run()
{
	//Creates a window that will be used for displaying sprites.
	m_window.create(sf::VideoMode(640, 480), "Blackjack");
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(false);

	//Game loop
	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		//Game step event
		Update();

		//Clear screen to black (by default)
		m_window.clear(sf::Color(31,163,66,255));

		//Actually draw stuff.
		Draw();
		
		//Draw screen buffer now that everything has been drawn to it.
		m_window.display();
	}
}

//A separate function for drawing, just to split up the main function.
void Game::Draw()
{
	//Render player deck.
	playerObj->getDeck()->drawDeck(320 - playerObj->getDeck()->getWidth(25) / 2, 300, 25);
	dealerObj->getDeck()->drawDeck(320 - dealerObj->getDeck()->getWidth(25) / 2, 100, 25);

	hitButton->draw();
	standButton->draw();
}

//A seperate function for the game step/ update.
void Game::Update()
{
	hitButton->step();
	standButton->step();

	//Hit Button
	if (hitButton->isRelease())
	{
		playerObj->Hit();
		std::cout << "Hit, deck now worth: " << playerObj->getDeck()->calculateTotal() << std::endl;
	}

	//Stand Button
	if (standButton->isRelease())
	{
		playerObj->Stand();
		std::cout << "Standing..." << std::endl;
	}
}

//Pretty much same parameters as the window draw function.
//Allows other classes to draw things simply.
sf::RenderWindow& Game::getWindow()
{
	return m_window;
}

Deck* Game::getMainDeck()
{
	return m_gameDeck;
}