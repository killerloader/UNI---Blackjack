#include <sstream>

#include "Game.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Resources.h"
#include "GameButton.h"

//Set singleton instance to nullptr.
Game* Game::m_thisInstance = nullptr;

//Get singleton function
Game& Game::instance()
{
	if (m_thisInstance == nullptr)
		m_thisInstance = new Game();

	return *m_thisInstance;
}

//Function to destroy the singleton and call its destructor.
void Game::destroy()
{
	delete this;				//Delete self and call destructor.
	m_thisInstance = nullptr;	//Set static singleton instance to nullptr.
}

//Removes implicit copy constructor.
Game::Game(Game& otherGame) {};

//Removes implicit copy assignment operator.
void Game::operator=(Game& otherGame) {};

//Game class constructor with initializer list for Deck class object which needs to call its constructor.
Game::Game()
{
	//Setup the symbol positions for the cards when they get rendered.
	setupSymbolPositions();

	//Create class pointers
	m_gameDeck = new Deck();

	//Create person objects (dealer and player)
	m_playerObj = new Player();
	m_dealerObj = new Dealer();

	//Create buttons
	m_hitButton = new GameButton(260, 430, 64, 25, "Hit", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_standButton = new GameButton(380, 430, 64, 25, "Stand", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_quitButton = new GameButton(320, 220, 64, 25, "Quit", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);
	m_playButton = new GameButton(320, 260, 64, 25, "Play", 20, sf::Color::Red, sf::Color::Green, sf::Color::Blue, true);

	//Create menubox rectangle.
	m_menuBox = new sf::RectangleShape(sf::Vector2f(200,100));
	m_menuBox->setPosition(220, 190);
	m_menuBox->setFillColor(sf::Color(0, 0, 0, 150));

	//Set playing to false so you start at the menu.
	m_playing = false;

	//Create the face down card sprite.
	m_cardBack = new sf::Sprite(*Resources::instance().findTexture("Card:Back"));
	m_cardBack->setOrigin((float)((int)m_cardBack->getLocalBounds().width / 2), (float)((int)m_cardBack->getLocalBounds().height / 2));
	m_cardBack->setPosition(540, 240);

	//Create the card that will be used for card animations when hitting.
	m_animationCard = new sf::Sprite();
	m_animAccel = 0.2f;
	m_animExpandSpeed = 0.08f;

	//Create the drawable text that will be used for displaying messages.
	m_gameMessage.setFont(Resources::instance().getFont());
	m_gameMessage.setCharacterSize(40);
	m_gameMessageSpeed = 4;
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
	delete m_quitButton;
	delete m_playButton;
	delete m_menuBox;
	delete m_cardBack;
	delete m_animationCard;
}

//A function to separate this from the constructor.
//This sets up positions of the symbols that are rendered to each card.
//The resources class actually does the rendering.
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
	Resources::instance().addToCardFormation(8, leftX, 35);//35 is above the middle, allows 4 symbols to fit.
	Resources::instance().addToCardFormation(8, rightX, 35);
	Resources::instance().addToCardFormation(8, leftX, 55);//55 is below the middle, allows 4 symbols to fit.
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
	m_window.create(sf::VideoMode(640, 480), "Blackjack", !sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(false);

	//Game loop
	while (m_window.isOpen())
	{
		sf::Event event;

		//Poll for windows events (closing window button)
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

	//Draw the "game message" animation. (Text to display messages)
	switch (m_gameMessageState)
	{
	case 1://Fade in
		//Increase alpha if it is not completely opaque.
		if (m_gameMessage.getColor().a + m_gameMessageSpeed >= 255)
		{
			m_gameMessage.setColor(sf::Color(0, 0, 0, 255));
			m_gameMessageState = 2;
		}
		else
			m_gameMessage.setColor(sf::Color(0, 0, 0, m_gameMessage.getColor().a + m_gameMessageSpeed));
		break;
	case 2://Fade out
		//Decrease alpha if it is not completely transparent.
		if (m_gameMessage.getColor().a - m_gameMessageSpeed <= 0)
			m_gameMessageState = 0;		

		m_gameMessage.setColor(sf::Color(0, 0, 0, m_gameMessage.getColor().a - m_gameMessageSpeed));
		break;
	}

	//Draw the "game message" text if it's state does not equal 0.
	if (m_gameMessageState)
		m_window.draw(m_gameMessage);

	//Draw card animation for when a player hits.
	switch (m_animationState)//Animating (not == 0)
	{
	case 1://Expanding
		//Increase scale
		m_animationCard->setScale(m_animationCard->getScale().x + m_animExpandSpeed, m_animationCard->getScale().y + m_animExpandSpeed);

		//Check if scale is max, if so, move onto the next animation step.
		if (m_animationCard->getScale().x >= 1)
		{
			m_animationCard->setScale(1, 1);
			m_animationState = 2;
		}
		break;

	case 2://Move towards deck.
	{
		//Increase speed
		m_animMoveSpeed += m_animAccel;

		/*
			------------------------------
			Uses triganometry tp find the angle to a point, then coverts an angular speed to 
			horizontal and vertical speeds.
			See more: https://en.wikipedia.org/wiki/Trigonometry
			------------------------------
		*/

		//Calculates the angle from the card to where it has to go to.
		float direction = atan2f(
			m_animToY - m_animationCard->getPosition().y
			,
			m_animToX - m_animationCard->getPosition().x
			);

		//Calculate horizontal and vertical speed.
		float xSpeed = m_animMoveSpeed*cosf(direction);
		float ySpeed = m_animMoveSpeed*sinf(direction);

		//Cards will always be moving left, so if the cardgoes more left than it's goto point
		//then stop moving and add it to the deck.
		//NOTE: If the deck were to be wide enough that the goto position was actually to the right, this would break, 
		//but that is not possible due to the minimum value of a deck this size.
		if (m_animationCard->getPosition().x + xSpeed <= m_animToX)
		{
			//Give the card to whoever started the animation.
			switch (m_animHitPerson)
			{
			case E_enumPlayer:m_playerObj->hit(); break;
			case E_enumDealer:m_dealerObj->hit(); break;
			}
			m_animationCard->setPosition(m_animToX, m_animToY);
			m_animationState = 0;//End animation.
		}
		else
			m_animationCard->move(xSpeed, ySpeed);

		break;
	}
	}

	//Draw card if it is currently being animated.
	if(m_animationState)
		m_window.draw(*m_animationCard);

	//Draw the menu buttons as we are not playing, and thus, in the menu.
	if (!m_playing)
	{
		m_window.draw(*m_menuBox);
		m_playButton->draw();
		m_quitButton->draw();
	}//If we are not in the menu, draw the game buttons.
	else if (!m_playerObj->isStanding() && !m_animationState && !m_gameMessageState)
	{
		m_hitButton->draw();
		m_standButton->draw();
	}
}

//A seperate function for the game step/ update.
void Game::update()
{
	//Boolean that check if either the player or the dealer needs to be dealt their first two cards.
	bool needToDeal =	((m_playerObj->getDeck()->getSize() < 2) && !m_playerObj->isStanding()) ||	//If players turn and needs to be dealt
						((m_dealerObj->getDeck()->getSize() < 2) && m_playerObj->isStanding());		//If dealers turn and needs to be dealt.
	//If we are not playing, run the buttons' update code.
	if (!m_playing)
	{
		//Update buttons.
		m_playButton->step();
		m_quitButton->step();

		//If released mouse over quit button, end the game by closing the window.
		if (m_quitButton->isRelease())
			m_window.close();

		//Start the game if this button is pressed.
		if (m_playButton->isRelease())
			startGame();
	}
	else if (needToDeal && !m_animationState) //If a person needs to be dealt two cards, and no card animation is occuring.
	{
		//Check if it is the player or the dealer who needs to be dealt cards.
		if (!m_playerObj->isStanding())//Player needs to be dealt
		{
			//Save card width and separation just to make it more neat.
			int cardWidth = 67;//Width of a card.
			int cardSep = 25;//Card separation.

			//Calculates where the new card will be so that the animation places it correctly.
			int newCardX = 320 + m_playerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

			//Starts the card dealing animation.
			startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumPlayer, (float)newCardX, 310.f + m_cardBack->getLocalBounds().height / 2.f);
		}
		else
		{
			//Save card width and separation just to make it more neat.
			int cardWidth = 67;//Width of a card.
			int cardSep = 25;//Card separation.

			//Calculates where the new card will be so that the animation places it correctly.
			int newCardX = 320 + m_dealerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

			//Starts the card dealing animation.
			startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumDealer, (float)newCardX, 170.f - m_cardBack->getLocalBounds().height / 2.f);
		}
	}
	else if (!m_animationState && !m_gameMessageState)//If there are no card or text animations.
	{
		//If it is the player's turn.
		if (!m_playerObj->isStanding())
		{
			//Update the game buttons, as the player can use them now.
			m_hitButton->step();
			m_standButton->step();

			if (m_playerObj->isBust())
			{
				//Show message and end game.
				startGameMessage(320, 25, "You lose! You went bust.");
				endGame(); return;
			}

			//If hit button is pressed (mouse released over it)
			if (m_hitButton->isRelease())
			{
				if (m_gameDeck->getSize() != 0)//Can take a card because game deck is not empty.
				{
					//Save card width and separation just to make it more neat.
					int cardWidth = 67;//Width of a card.
					int cardSep = 25;//Card separation.

					//Calculates where the new card will be so that the animation places it correctly.
					int newCardX = 320 + m_playerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

					//Starts the card dealing animation.
					startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumPlayer, (float)newCardX, 310.f + m_cardBack->getLocalBounds().height / 2.f);
				}
			}

			//Stand Button
			if (m_standButton->isRelease())
			{
				//Stop the player's turn and go to the dealers turn.
				m_playerObj->stand();
				startGameMessage(320, 25, "Dealer's turn");
			}
		}
		else//Dealers turn.
		{
			if (m_dealerObj->isBust())
			{
				//Send message about player winning and end game.
				startGameMessage(320, 25, "You win! The dealer went bust");
				endGame(); return;
			}
			
			//If the dealer's deck is not worth more than the player's, then hit.
			if (m_dealerObj->getDeck()->calculateTotal() <= m_playerObj->getDeck()->calculateTotal())//Hit until larger or bust.
			{
				//Save card width and separation just to make it more neat.
				int cardWidth = 67;//Width of a card.
				int cardSep = 25;//Card separation.

				//Calculates where the new card will be so that the animation places it correctly.
				int newCardX = 320 + m_playerObj->getDeck()->getWidth(cardSep) / 2 + (cardWidth - cardSep) / 2 - cardWidth / 2;

				//Starts the card dealing animation.
				startAnimation(*(*m_gameDeck)[m_gameDeck->getSize() - 1]->getSprite().getTexture(), E_enumDealer, (float)newCardX, (float)(170.f - m_cardBack->getLocalBounds().height / 2.f));
			}
			else
			{
				//The dealer's combination of cards was worth more than the player's, and he didn't go bust.
				startGameMessage(320, 25, "You lose!");
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

//Resets everything to a new game state.
//Also sends a message saying that it's the player's turn.
void Game::startGame()
{
	//Reset all the decks in the game, and generate a new main deck.
	m_playerObj->reset();
	m_dealerObj->reset();
	m_gameDeck->generateMainDeck();

	startGameMessage(320, 25, "Your turn!");

	m_playing = true;
}

//Starts the card animation when a person hits.
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

//Starts a message.
//This message blocks the player or the dealer from doing anything until it's gone.
//The player/ dealer can still be dealt their first two cards while this is shown.
void Game::startGameMessage(const int& x, const int& y, const char* message)
{
	m_gameMessageState = 1;
	m_gameMessage.setColor(sf::Color(0,0,0,0));
	m_gameMessage.setString(message);
	m_gameMessage.setOrigin(m_gameMessage.getLocalBounds().width / 2 + m_gameMessage.getLocalBounds().left, m_gameMessage.getLocalBounds().height / 2 + m_gameMessage.getLocalBounds().top);//Center the origin.
	m_gameMessage.setPosition((float)x, (float)y);
}

//Pretty much same parameters as the window draw function.
//Allows other classes to draw things simply.
sf::RenderWindow& Game::getWindow()
{
	return m_window;
}

//Returns the main game deck.
Deck* Game::getMainDeck()
{
	return m_gameDeck;
}