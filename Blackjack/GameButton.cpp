#include "GameButton.h"
#include "Game.h"

GameButton::GameButton(Game& GRef, int x, int y, int width, int height, const char* buttonText, int fontSize, const sf::Color& startColour, const sf::Color& hoverColour, const sf::Color& pressColour, bool centered) : m_gameRef(GRef)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_startColour = startColour;
	m_hoverColour = hoverColour;
	m_pressColour = pressColour;

	m_button.setPosition((float)m_x, (float)m_y);
	m_button.setSize(sf::Vector2f((float)m_width, (float)m_height));
	if (centered)
		m_button.setOrigin(m_button.getLocalBounds().width / 2, m_button.getLocalBounds().height / 2);
	m_button.setFillColor(m_startColour);
	m_button.setOutlineColor(sf::Color::Black);
	m_button.setOutlineThickness(1);

	m_buttonText.setCharacterSize(fontSize);
	m_buttonText.setFont(Resources::instance().getFont());
	m_buttonText.setString(buttonText);
	m_buttonText.setOrigin(m_buttonText.getLocalBounds().left + m_buttonText.getLocalBounds().width / 2, m_buttonText.getLocalBounds().top + m_buttonText.getGlobalBounds().height/2);
	m_buttonText.setPosition(m_x - m_button.getOrigin().x + m_width / 2.f, m_y - m_button.getOrigin().y + m_height / 2.f);

	m_MBLDown = false;
	m_MBLPressed = false;
	m_MBLReleased = false;
}

GameButton::~GameButton()
{

}

void GameButton::draw()
{
	m_gameRef.getWindow().draw(m_button);
	m_gameRef.getWindow().draw(m_buttonText);
}

//This pretty much just polls the mouse pressed event.
void GameButton::step()
{
	//The first time the button is pressed "m_MBLDown" will be false, so "m_MBLPressed" will become true.
	m_MBLPressed = (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_MBLDown);
	m_MBLReleased = (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MBLDown);
	m_MBLDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (isHover())
	{
		if (m_MBLDown)
			m_button.setFillColor(m_pressColour);
		else
			m_button.setFillColor(m_hoverColour);
	}
	else
		m_button.setFillColor(m_startColour);
}

bool GameButton::isHover()
{
	//Check if mouse positition is within the box of the button.
	return (sf::Mouse::getPosition(m_gameRef.getWindow()).x >= m_x - m_button.getOrigin().x &&
			sf::Mouse::getPosition(m_gameRef.getWindow()).y >= m_y - m_button.getOrigin().y &&
			sf::Mouse::getPosition(m_gameRef.getWindow()).x <= m_x - m_button.getOrigin().x + m_width &&
			sf::Mouse::getPosition(m_gameRef.getWindow()).y <= m_y - m_button.getOrigin().y + m_height);
}

bool GameButton::isPress()
{
	return (isHover() && m_MBLPressed);
}

bool GameButton::isRelease()
{
	return (isHover() && m_MBLReleased);
}