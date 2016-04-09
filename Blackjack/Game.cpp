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

	m_playerObj = new Player(*this);
	m_dealerObj = new Dealer(*this);

	m_hitButton = new GameButton(*this, 260, 430, 64, 25, "Hit", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_standButton = new GameButton(*this, 380, 430, 64, 25, "Stand", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_quitButton = new GameButton(*this, 320, 220, 64, 25, "Quit", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_playButton = new GameButton(*this, 320, 260, 64, 25, "Play", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);

	m_menuBox = new sf::RectangleShape(sf::Vector2f(200,100));
	m_menuBox->setPosition(220, 190);
	m_menuBox->setFillColor(sf::Color(0, 0, 0, 150));

	m_playing = false;

	Resources::instance().findTexture("Card:Back")->setSmooth(true);

	m_cardBack = new sf::Sprite(*Resources::instance().findTexture("Card:Back"));
	m_cardBack->setOrigin((float)((int)m_cardBack->getLocalBounds().width / 2), (float)((int)m_cardBack->getLocalBounds().height / 2));
	m_cardBack->setPosition(540, 240);

	m_animationCard = new sf::Sprite();
	m_animAccel = 0.2f;
	m_animExpandSpeed = 0.08f;

	//Start the game, which will generate the main deck, and clear the player decks (which should be clear already)
	//startGame();
}

//Game class destructor
Game::~Game()
{
	//Destroy pointers
	delete m_gameDeck;
	delete m_playerObj;
	delete m_dealerObj;
	delete m_hitButton;
	delete m_standButton;
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
void Game::run()
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
		update();

		//Clear screen to black (by default)
		m_window.clear(sf::Color(31,163,66,255));

		//Actually draw stuff.
		draw();
		
		//Draw screen buffer now that everything has been drawn to it.
		m_window.display();
	}
}

//A separate function for drawing, just to split up the main function.
void Game::draw()
{
	//Render player deck.
	m_playerObj->getDeck()->drawDeck(320 - m_playerObj->getDeck()->getWidth(25) / 2, 310, 25);
	m_dealerObj->getDeck()->drawDeck(320 - m_dealerObj->getDeck()->getWidth(25) / 2, 170 - m_playerObj->getDeck()->getHeight(), 25);

	//Draw the face down card.
	m_window.draw(*m_cardBack);

	//Draw card animation for when a player hits.
	switch (m_animationState)//Animating (not == 0)
	{
	case 0://Empty case
		break;

	case 1://Expanding
		m_animationCard->setScale(m_animationCard->getScale().x + m_animExpandSpeed, m_animationCard->getScale().y + m_animExpandSpeed);

		if (m_animationCard->getScale().x >= 1)
		{
			m_animationCard->setScale(1, 1);
			m_animationState = 2;
		}
		break;

	case 2://Move towards deck.
		m_animMoveSpeed += m_animAccel;

		float direction = atan2f(
			m_animToY - m_animationCard->getPosition().y
			,
			m_animToX - m_animationCard->getPosition().x
		);

		float xSpeed = m_animMoveSpeed*cosf(direction);
		float ySpeed = m_animMoveSpeed*sinf(direction);

		if (m_animationCard->getPosition().x + xSpeed <= m_animToX)
		{
			//Give the card to whoever started the animation.
			switch (m_animHitPerson)
			{
			case E_enumPlayer:m_playerObj->hit(); break;
			case E_enumDealer:m_dealerObj->hit(); break;
			}

			m_animationState = 0;//End animation.
		}


		m_animationCard->move(xSpeed, ySpeed);
		break;
	}

	if(m_animationState)
		m_window.draw(*m_animationCard);

	if (!m_playing)
	{
		m_window.draw(*m_menuBox);
		m_playButton->draw();
		m_quitButton->draw();
	}
	else if (!m_playerObj->isStanding() && !m_animationState)
	{
		m_hitButton->draw();
		m_standButton->draw();
	}
}

//A seperate function for the game step/ update.
void Game::update()
{
	if (!m_animationState)
	{
		if (!m_playing)
		{
			m_playButton->step();
			m_quitButton->step();

			if (m_quitButton->isRelease())
				m_window.close();

			if (m_playButton->isRelease())
				startGame();
		}
		else if (!m_playerObj->isStanding())
		{
			m_hitButton->step();
			m_standButton->step();

			if (m_playerObj->isBust())
			{
				std::cout << "You have gone bust, therefore you lose." << std::endl;
				endGame(); return;
			}

			//Hit Button
			if (m_hitButton->isRelease())
			{
				//Card* animCard = m_playerObj->hit();
				if (m_gameDeck->getSize() != 0)//Can take a card because not empty.
				{
					//Save card width and separation just to make it more neat.
					int cardWidth = 67;//Width of a card.
					int cardSep = 25;//Card separation.

					//Calculates where the new card will be so that the animation places it correctly.
					int newCardX = 320 + m_playerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

					//Starts the card dealing animation.
					startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumPlayer, (float)newCardX, 310.f + (float)m_playerObj->getDeck()->getHeight() / 2.f);
				}
			}

			//Stand Button
			if (m_standButton->isRelease())
			{
				m_playerObj->stand();

				//Deal two cards to the dealer.
				m_dealerObj->hit();
				m_dealerObj->hit();
				std::cout << "Standing..." << std::endl;
			}
		}
		else//Dealers turn.
		{
			if (m_dealerObj->isBust())
			{
				std::cout << "The dealer has gone bust, and therefore you win!" << std::endl;
				endGame(); return;
			}

			if (m_dealerObj->getDeck()->calculateTotal() <= m_playerObj->getDeck()->calculateTotal())//Hit until larger or bust.
			{
				//Save card width and separation just to make it more neat.
				int cardWidth = 67;//Width of a card.
				int cardSep = 25;//Card separation.

				//Calculates where the new card will be so that the animation places it correctly.
				int newCardX = 320 + m_playerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

				//Starts the card dealing animation.
				startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumDealer, (float)newCardX,(float)(170 - m_playerObj->getDeck()->getHeight() / 2));
			}
			else
			{
				std::cout << "The dealer gets a better set of cards than you, so he wins." << std::endl;
				endGame();
			}
		}
	}
}

//Just sets playing to false, will show the menu again (while showing the previous game results)
void Game::endGame()
{
	m_playing = false;
}

void Game::startGame()
{
	//Reset all the decks in the game, and generate a new main deck.
	m_playerObj->reset();
	m_dealerObj->reset();
	m_gameDeck->generateMainDeck();

	//Deal two cards to the player.
	m_playerObj->hit();
	m_playerObj->hit();

	m_playing = true;
}

void Game::startAnimation(const sf::Texture& cardTex, E_personType whoHit, float flyToX, float flyToY)
{
	m_animationState = 1;//Playing;
	m_animationCard->setTexture(cardTex);
	m_animationCard->setOrigin((float)((int)m_animationCard->getLocalBounds().width / 2), (float)((int)m_animationCard->getLocalBounds().height / 2));
	m_animationCard->setScale(0, 0);
	m_animationCard->setPosition(540, 240);
	m_animMoveSpeed = 0;
	m_animHitPerson = whoHit;
	m_animToX = flyToX;
	m_animToY = flyToY;
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