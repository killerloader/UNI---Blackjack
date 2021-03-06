#include "GameButton.h"
#include "Game.h"

//Gamebutton constructor, takes a few arguments which basically define how it will behave.
GameButton::GameButton(int x, int y, int width, int height, const char* buttonText, int fontSize, const sf::Color& startColour, const sf::Color& hoverColour, const sf::Color& pressColour, bool centered)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_startColour = startColour;
	m_hoverColour = hoverColour;
	m_pressColour = pressColour;

	//Set many of the actual drawable object's traits.
	//Cast to float to avoid errors, use ints to avoid having things inbetween pixels.
	m_button.setPosition((float)m_x, (float)m_y);
	m_button.setSize(sf::Vector2f((float)m_width, (float)m_height));

	//Check if the button should be centered.
	if (centered)
		m_button.setOrigin(m_button.getLocalBounds().width / 2, m_button.getLocalBounds().height / 2);

	m_button.setFillColor(m_startColour);
	m_button.setOutlineColor(sf::Color::Black);
	m_button.setOutlineThickness(1);

	//Setup button text.
	m_buttonText.setCharacterSize(fontSize);
	m_buttonText.setFont(Resources::instance().getFont());
	m_buttonText.setString(buttonText);
	m_buttonText.setOrigin(m_buttonText.getLocalBounds().left + m_buttonText.getLocalBounds().width / 2, m_buttonText.getLocalBounds().top + m_buttonText.getGlobalBounds().height/2);
	m_buttonText.setPosition(m_x - m_button.getOrigin().x + m_width / 2.f, m_y - m_button.getOrigin().y + m_height / 2.f);

	//Define input (mouse button left)
	m_mBLDown = false;
	m_mBLPressed = false;
	m_mBLReleased = false;
}

//Draw the button and the text that goes on it.
void GameButton::draw()
{
	Game::instance().getWindow().draw(m_button);
	Game::instance().getWindow().draw(m_buttonText);
}

//Step event of the button.
//This keeps track of if a button was just pressed or released.
void GameButton::step()
{
	//The first time the button is pressed "m_MBLDown" will be false, so "m_MBLPressed" will become true.
	m_mBLPressed = (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mBLDown);
	m_mBLReleased = (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mBLDown);
	m_mBLDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (isHover())
	{
		if (m_mBLDown)
			m_button.setFillColor(m_pressColour);
		else
			m_button.setFillColor(m_hoverColour);
	}
	else
		m_button.setFillColor(m_startColour);
}

//Returns true if the mouse is hovering over this button.
bool GameButton::isHover()
{
	//Check if mouse positition is within the box of the button.
	return (sf::Mouse::getPosition(Game::instance().getWindow()).x >= m_x - m_button.getOrigin().x &&
			sf::Mouse::getPosition(Game::instance().getWindow()).y >= m_y - m_button.getOrigin().y &&
			sf::Mouse::getPosition(Game::instance().getWindow()).x <= m_x - m_button.getOrigin().x + m_width &&
			sf::Mouse::getPosition(Game::instance().getWindow()).y <= m_y - m_button.getOrigin().y + m_height);
}

//Checks if the left mouse button was pressed, and the mouse was hovering over the button.
bool GameButton::isPress()
{
	return (isHover() && m_mBLPressed);
}

//Checks if the left mouse button was released, and the mouse was hovering over the button.
bool GameButton::isRelease()
{
	return (isHover() && m_mBLReleased);
}