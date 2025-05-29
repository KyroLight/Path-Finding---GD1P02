//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Button.cpp												   ==
//== Description : Has implementation for buttons and states and things	   ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


#include "Button.h"

void Button::updateState()
{
	switch (m_state)
	{

	case (normal):
	{
		m_shape.setFillColor(sf::Color::Green);
		break;
	}
	case (hover):
	{
		m_shape.setFillColor(sf::Color::Yellow);
		break;
	}
	case (press):
	{
		m_shape.setFillColor(sf::Color::Red);
		break;
	}
	default:
	{
		break;
	}

	}
}

void Button::updateButton(const sf::RenderWindow& _window)
{
	if (m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
	{
		m_state = hover;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_state = press;
		}
	}
	else
	{
		m_state = normal;
	}

	updateState();

}

Button::Button(int _x, int _y, std::string _text) : m_font("Brunson.ttf"), m_text(m_font)
{
	m_shape.setSize(sf::Vector2f(150, 50));
	m_shape.setPosition(sf::Vector2f(_x, _y));

	m_text.setFillColor(sf::Color::Black);
	m_text.setString(_text);
	m_text.setCharacterSize(20);
	m_text.setPosition(sf::Vector2f(_x, _y));

	m_state = normal;
}

Button::~Button()
{
}
