#pragma once

/*
	GameButton.h/ GameButton.cpp
		A button that can be drawn to the screen.
		Handles mouse pressing and releasing for button actions.
*/

#include <SFML/Graphics.hpp>

class Game;

class GameButton
{
public:
	//Constructor, takes in everything needed by the button.
	GameButton(Game& gameRef, int x, int y, int width, int height, const char* buttonText, int fontSize, const sf::Color& startColour, const sf::Color& hoverColour, const sf::Color& pressColour, bool centered = false);
	
	void step();		//Update event for button, polls input.
	void draw();		//Draw event for button, draws button and text.
	bool isHover();		//Returns if the mouse is over the button.
	bool isPress();		//Returns if the mouse was pressed on the button.
	bool isRelease();	//Returns if the mouse was released on the button.

private:
	int m_x, m_y, m_width, m_height;//Button dimensions.
	Game& m_gameRef;				//Reference to main game object.
	sf::RectangleShape m_button;	//Drawable rectangle for the button.
	sf::Text m_buttonText;			//Text that goes with the button. In drawable format.
	bool m_mBLDown;					//Keeps track of if MBL is held down.
	bool m_mBLPressed;				//Is true for one frame after MBL is pressed.
	bool m_mBLReleased;				//Is true for one frame after MBL is pressed.

	//Colours of the button depending on certain situations.
	sf::Color m_startColour, m_hoverColour, m_pressColour;
};

