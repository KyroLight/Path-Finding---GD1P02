#pragma once

//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Node.h													   ==
//== Description : Node class used for traversing and pathfinding          ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/

#include <SFML/Graphics.hpp>


enum NodeState
{
	//for SFML visuals
	emptyState,
	openState,
	closedState,
	pathState
};

class Node {

//NODE STUFF
public:
	Node* m_parent;
	int row;
	int column;
	float m_gCost;
	float m_hCost;
	float m_fCost;
	char m_key;
	std::vector<Node*> m_neighbours;

	float fCost();


	Node(sf::Color _color, int _row, int _column, char _key, sf::Font _font);
	~Node();


//SFML STUFF
public:
	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;

	void updateColor(NodeState _state);

private:
	NodeState state;
	sf::Color m_startingColor;

};