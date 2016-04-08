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
class Game
{
public:
	Game();							//Constructor
	~Game();						//Destructor
	void Run();						//Game main event.
	void Draw();					//Game draw/ render event.
	void Update();					//Game step event.
	void setupSymbolPositions();	//Sets up the symbol positioning of cards A to 10
	Deck* getMainDeck();			//Getter for the game deck.
	sf::RenderWindow& getWindow();  //

private:
	Deck* m_gameDeck;				//Pointer to the game/ main deck.
	sf::RenderWindow m_window;		//Game window.
	Player* playerObj;
	Dealer* dealerObj;
	GameButton* hitButton;
	GameButton* standButton;
};

