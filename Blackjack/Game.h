#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.h"

#include <vector>

class Deck;

/*
	Game.h/ Game.cpp
		
*/

//Game class definition.
class Game
{
public:
	Game();							//Constructor
	~Game();						//Destructor
	void Run();						//Game step event
	void Draw();					//Game draw/ render event.
	void setupSymbolPositions();	//Sets up the symbol positioning of cards A to 10
	Deck* getGameDeck();			//Getter for the game deck.

private:
	Deck* m_gameDeck;				//Pointer to the game/ main deck.
	sf::RenderWindow m_window;		//Game window.
};

