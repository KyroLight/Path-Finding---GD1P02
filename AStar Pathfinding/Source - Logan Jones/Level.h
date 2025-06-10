#pragma once

//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Level.h												   ==
//== Description : Made for loading in levels and whatnot                  ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


//THIS ENTIRE PAGE IS A MESS AND YES IT SUCKS BUT IT WORKS I THINK AND THATS WHAT MATTERS

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <string>

#include "Node.h"


//comparisons for fCost for std::set
struct fCostComparison
{
	bool const operator()(Node* _lhs, Node* _rhs) const
	{
		return _lhs->fCost() > _rhs->fCost();
	}
};


class Level {

//LEVEL STUFF
private:
	
	//distance comparison for std::sort function in BREADTH FIRST SEARCHING
	//to find the smallest distance value for neighbours
	struct distanceComparison
	{
		Node* current;
		Level* level;

		distanceComparison(Node* _current, Level* _level) : current(_current), level(_level) {}

		bool operator()(Node* _a, Node* _b)
		{
			return level->euclideanDistance(current, _a) < level->euclideanDistance(current, _b);
		}
	};

	

	sf::Vector2i m_startPos; 
	sf::Vector2i m_endPos;

	std::map<char, std::string> m_letterLookup;

	

	//helper functions
	bool validateLevel();

	float calculateHCost(Node* _current, Node* _end);
	bool depthFirstRecursive(int _row, int _column, std::vector<std::vector<bool>>& _checked, int& _collected);

	std::vector<Node*> highlightPath(Node* _end, bool _changeKey);
	std::vector<Node*> connectNeighbours(int _row, int _column);

	std::vector<std::vector<char>> m_rawLevelData;


public:

	Level();
	~Level();

	sf::Font g_font;

	bool loadLevel(std::string _filepath);
	void setLevel();
	void unloadLevel();
	
	std::vector<std::vector<Node*>> m_graphData;
	
	float euclideanDistance(Node* _a, Node* _b);
	bool compareFCost(Node* a, Node* b);

	Node* getStart();
	Node* getEnd();

	std::vector<Node*> aStarPathfinding(Node* _start, Node* _end);
	void saveAStarPath(std::string _filepath);


	void depthFirst();
	void breadthFirst(Node* _start);

	void bullshitPlayaroundColors();
	std::string openFileDialog();
	std::string saveFileDialog();
};

