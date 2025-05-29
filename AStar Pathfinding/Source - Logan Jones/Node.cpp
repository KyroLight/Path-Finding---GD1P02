//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Node.cpp												   ==
//== Description : Constructor and data setting for Node class			   ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


#include "Node.h"


//-------------------------CONSTRUCTOR_&_DESTRUCTOR-------------------------//
Node::Node(sf::Color _color, int _row, int _column, char _key, sf::Font _font) : m_font(_font), m_text(m_font)
{
	//NODE DEFAULT VALUES
	m_parent = nullptr;
	row = _row;
	column = _column;
	m_gCost = std::numeric_limits<float>::max();
	m_hCost = 0.0f;
	m_fCost = fCost();
	m_key = _key;
	



	//SFML STUFF FOR VISUAL OUTPUT
	state = emptyState;

	m_shape.setFillColor(_color);
	m_shape.setPosition(sf::Vector2f(_column * 50, _row * 50));
	m_shape.setSize(sf::Vector2f(50, 50));
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(0.7f);

	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(30);
	m_text.setPosition(sf::Vector2f(_column * 50 + (m_shape.getSize().x / 2.65f), _row * 50 + (m_shape.getSize().y / 6.0f)));

	m_startingColor = m_shape.getFillColor();
}
Node::~Node()
{
}
//--------------------------------------------------------------------------//



//-------------------------NODE_MATH-------------------------//
float Node::fCost()
{
	return m_gCost + m_hCost;
}
//-----------------------------------------------------------//



//-------------------------SFML_VISUAL-------------------------//
void Node::updateColor(NodeState _state)
{
	switch (_state)
	{
	case openState:
	{
		m_shape.setFillColor(sf::Color::Color(144, 238, 144));
		break;
	}
	case closedState:
	{
		m_shape.setFillColor(sf::Color::Color(173, 216, 230));
		break;
	}
	case pathState:
	{
		m_shape.setFillColor(sf::Color::Yellow);
		break;
	}
	case emptyState:
	{
		m_shape.setFillColor(m_startingColor);
		break;
	}
	default:
	{
		break;
	}
	}
}
//-------------------------------------------------------------//