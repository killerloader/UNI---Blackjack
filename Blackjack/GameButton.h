#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameButton
{
public:
	GameButton(Game& GRef, int x, int y, int width, int height, const char* buttonText, int fontSize, const sf::Color& startColour, const sf::Color& hoverColour, const sf::Color& pressColour, bool centered = false);
	~GameButton();
	void step();
	void draw();
	bool isHover();
	bool isPress();
	bool isRelease();

private:
	int m_x, m_y, m_width, m_height;
	Game& m_gameRef;
	sf::RectangleShape m_button;
	sf::Text m_buttonText;
	bool m_MBLDown;					//Keeps track of if MBL is held down.
	bool m_MBLPressed;				//Is true for one frame after MBL is pressed.
	bool m_MBLReleased;				//Is true for one frame after MBL is pressed.
	sf::Color m_startColour, m_hoverColour, m_pressColour;
};

