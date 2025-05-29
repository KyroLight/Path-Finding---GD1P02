#pragma once

//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Button.h												   ==
//== Description : Definitions for buttons and some super basic stuff      ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


#include <SFML/Graphics.hpp>


enum ButtonState {
	normal,
	hover,
	press
};

class Button {

public:
	sf::RectangleShape m_shape;
	ButtonState m_state;
	sf::Font m_font;
	sf::Text m_text;

	void updateState();
	void updateButton(const sf::RenderWindow& _window);

	Button(int _x, int _y, std::string _text);
	~Button();
};

