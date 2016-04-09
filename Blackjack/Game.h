#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.h"

#include <vector>

class Deck;
class Player;
class Dealer;
class GameButton;

/*
	Game.h/ Game.cpp
		
*/

//Game class definition.
enum E_personType
{
	E_enumPlayer,
	E_enumDealer
};

class Game
{
public:
	Game();							//Constructor
	~Game();						//Destructor
	void run();						//Game main event.
	void draw();					//Game draw/ render event.
	void update();					//Game step event.
	void setupSymbolPositions();	//Sets up the symbol positioning of cards A to 10
	void startGame();				//Resets decks and statuses.
	void endGame();					//Stops the game and opens the menu. (still shows the 
	Deck* getMainDeck();			//Getter for the game deck.
	sf::RenderWindow& getWindow();  //Returns a reference to the game window.

private:
	Deck* m_gameDeck;				//Pointer to the game/ main deck.
	sf::RenderWindow m_window;		//Game window.
	Player* m_playerObj;			//Player object
	Dealer* m_dealerObj;			//Dealer object
	GameButton* m_hitButton;		//Instance of hit button
	GameButton* m_standButton;		//Instance of stand button
	GameButton* m_quitButton;		//Instance of quit button
	GameButton* m_playButton;		//Instance of play button
	sf::RectangleShape* m_menuBox;	//The rectangle that holds menu buttons (quit and play)
	sf::Sprite* m_cardBack;			//The sprite of a face down card.
	sf::Sprite* m_animationCard;	//A sprite used for card animations.

	//A function to start the main card animation.
	void startAnimation(const sf::Texture &cardTex, E_personType whoHit, float flyToX, float flyToY);

	//Animation variables.
	int m_animationState;			//Animation for when you get a card.
	float m_animMoveSpeed;			//How fast the card moves to its destination.
	float m_animAccel;				//The acceleration of the card's speed.
	float m_animExpandSpeed;		//How fast the card expands in its first animation.
	float m_animToX;				//Where the card will fly to in the animation
	float m_animToY;				//^^
	E_personType m_animHitPerson;	//Enum for if a card animation belongs to the player or the dealer.

	sf::Text gameMessage;			//A message that shows the status of the game.
	bool m_playing;					//Boolean for if you are playing or in the menu.
};

