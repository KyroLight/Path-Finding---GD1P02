//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : Level.cpp												   ==
//== Description : Implementation for level loading, unloading and setting ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


#include "Level.h"


//-------------------------CONSTRUCTOR_&_DESTRUCTOR-------------------------//
Level::Level() : g_font("Brunson.ttf")
{
	//make the array the right size and fill it with empty nodes
	m_rawLevelData = std::vector<std::vector<char>>(20, std::vector<char>(20, '.'));


	//make the graphData the right size
	m_graphData.resize(m_rawLevelData.size());
	for (size_t i = 0; i < m_rawLevelData.size(); i++)
	{
		m_graphData[i].resize(m_rawLevelData[i].size(), nullptr);
	}

	//map used if letters in level is not in alphabetical order in book style (left to right, top to bottom)
	m_letterLookup = {
		{'a', "1"},
		{'b', "2"},
		{'c', "3"},
		{'d', "4"},
		{'e', "5"},
		{'f', "6"},
		{'g', "7"},
		{'h', "8"},
		{'i', "9"},
		{'j', "10"} 
	};
}
Level::~Level()
{
}
//--------------------------------------------------------------------------//



//-------------------------LEVEL_&_NEIGHBOURS-------------------------//
bool Level::loadLevel(std::string _filepath)
{

	std::fstream fileStream;
	fileStream.open(_filepath);

	std::string fileLine;
	int lineCount = 0;


	if (fileStream.is_open())
	{
		while (std::getline(fileStream, fileLine))
		{

			for (size_t i = 0; i < fileLine.size(); i++)
			{
				m_rawLevelData[lineCount][i] = fileLine[i];
			}

			lineCount++;

		}
		fileStream.close();
	}

	if (!validateLevel())
	{
		std::cerr << "file is invalid" << std::endl;
		//fill the array with trash because the program will still run with an invalid map loaded in.
		//not what i want so fill with bullshit
		for (size_t i = 0; i < m_rawLevelData.size(); i++)
		{
			for (size_t j = 0; j < m_rawLevelData[i].size(); j++)
			{
				m_rawLevelData[i][j] = '.';
			}
		}
		return false;
	}

	setLevel();

	return true;
}
std::vector<Node*> Level::connectNeighbours(int _row, int _column)
{
	std::vector<Node*> neighbours;
	//calculate each neighbour 
	std::vector<sf::Vector2i> surroundings = {  {-1, -1},  {0, -1},   {1, -1},
												{-1, 0} ,			  {1, 0} ,
												{-1, 1} ,   {0, 1},   {1, 1} };

	for (size_t i = 0; i < surroundings.size(); i++)
	{
		int newRow = _row + surroundings[i].x;
		int newColumn = _column + surroundings[i].y;

		//to ensure it stays within the 2D array
		if (newRow >= 0 && newRow < m_graphData.size())
		{
			if (newColumn >= 0 && newColumn < m_graphData[newRow].size())
			{
				//dont add walls as viable neighbours to avoid checking against walls later;
				if (m_graphData[newRow][newColumn]->m_key != 'w')
				{
					neighbours.push_back(m_graphData[newRow][newColumn]);
				}
			}
		}
	}

	return neighbours;
}
bool Level::validateLevel()
{
	int startNum = 0;
	int endNum = 0;
	std::vector<char> items;

	for (size_t row = 0; row < m_rawLevelData.size(); row++)
	{
		for (size_t column = 0; column < m_rawLevelData[row].size(); column++)
		{
			if (m_rawLevelData[row][column] == 's')
			{
				startNum++;
			}
			else if (m_rawLevelData[row][column] == 'x')
			{
				endNum++;
			}
			else if (m_rawLevelData[row][column] >= 'a' && m_rawLevelData[row][column] <= 'j')
			{
				items.push_back(m_rawLevelData[row][column]);
			}
			else if (m_rawLevelData[row][column] != 'w' && m_rawLevelData[row][column] != '.')
			{
				//if object in rawLevelData is not a valid block, return false
				return false;
			}
		}
	}

	//final viability check
	if (startNum == 1 && endNum == 1 && items.size() == 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Level::setLevel()
{
	//iterating through rawLevelData and creating the level/graph
	for (size_t row = 0; row < m_rawLevelData.size(); row++)
	{
		for (size_t column = 0; column < m_rawLevelData[row].size(); column++)
		{
			char key = m_rawLevelData[row][column];

			if (key == 'w')
			{
				Node* mapWall = new Node(sf::Color(150, 150, 150), row, column, 'w', g_font);
				m_graphData[row][column] = mapWall;
			}
			else if (key == '.')
			{
				Node* mapDefault = new Node(sf::Color::White, row, column, '.', g_font);
				m_graphData[row][column] = mapDefault;
			}
			else if (key == 's')
			{
				Node* mapStart = new Node(sf::Color::Green, row, column, 's', g_font);
				m_startPos = sf::Vector2i(row, column);
				m_graphData[row][column] = mapStart;
			}
			else if (key == 'x')
			{
				Node* mapEnd = new Node(sf::Color::Red, row, column, 'x', g_font);
				m_endPos = sf::Vector2i(row, column);
				m_graphData[row][column] = mapEnd;
			}
			else if (m_letterLookup.count(key))
			{
				Node* mapItem = new Node(sf::Color::White, row, column, key, g_font);
				mapItem->m_text.setString(m_letterLookup[key]);
				m_graphData[row][column] = mapItem;
			}
		}
	}

	//setting the neighbours for each block. skipping wall blocks happens inside of connectNeighbours;
	for (size_t row = 0; row < m_rawLevelData.size(); row++)
	{
		for (size_t column = 0; column < m_rawLevelData[row].size(); column++)
		{
			m_graphData[row][column]->m_neighbours = connectNeighbours(row, column);
		}
	}

#ifdef _DEBUG

	//debug to print out each node and the list of neighbours it has.
	for (size_t row = 0; row < m_rawLevelData.size(); row++)
	{
		for (size_t column = 0; column < m_rawLevelData[row].size(); column++)
		{
			Node* current = m_graphData[row][column];
			std::cout << "Neighbours of Node [" << row << "," << column << "] (" << current->m_key << "): \n";

			for (Node* neighbour : current->m_neighbours)
			{
				std::cout << "row: " << neighbour->row << " , column: " << neighbour->column << " , '" << neighbour->m_key << "' \n";
			}

			std::cout << std::endl;
		}
	}

#endif // _DEBUG
}
void Level::unloadLevel()
{
	for (auto& row : m_graphData)
	{
		for (Node*& node : row)
		{
			delete node;
			node = nullptr;
		}
	}

	m_graphData.clear();

	m_graphData.resize(m_rawLevelData.size());

	for (size_t i = 0; i < m_rawLevelData.size(); i++)
	{
		m_graphData[i].resize(m_rawLevelData[i].size());
	}
}
//--------------------------------------------------------------------//



//-------------------------GETTERS-------------------------//
Node* Level::getStart()
{
	return m_graphData[m_startPos.x][m_startPos.y];
}
Node* Level::getEnd()
{
	return m_graphData[m_endPos.x][m_endPos.y];
}
//---------------------------------------------------------//



//-------------------------HELPERS-------------------------//
float Level::euclideanDistance(Node* _fromNode, Node* _toNode)
{
	//checking for diagonal movement
	if (_fromNode->row != _toNode->row && _fromNode->column != _toNode->column)
	{
		Node* rowNeighbour = m_graphData[_fromNode->row][_toNode->column];
		Node* columnNeighbour = m_graphData[_toNode->row][_fromNode->column];

		// Check if adjacent squares are free (not walls)
		if (rowNeighbour->m_key == 'w' || columnNeighbour->m_key == 'w')
		{

			//stop diagonal movement, only works when using infinity????
			return std::numeric_limits<float>::infinity();

		}

		//rounded sqrt of 2
		return 1.414f;

	}
	return 1.0f;
}
bool Level::compareFCost(Node* a, Node* b)
{
	float fCostA = a->m_gCost + a->m_hCost;
	float fCostB = b->m_gCost + b->m_hCost;
	return fCostA > fCostB;
}
float Level::calculateHCost(Node* _current, Node* _end)
{
	float rhs = abs(_current->row - _end->row);
	float lhs = abs(_current->column - _end->column);
	return rhs + lhs;
}
std::string Level::openFileDialog()
{
	//THIS WAS TAKEN FROM A THREAD AND USED AI TO MAKE IT FUNCTION
	//I DO NOT UNDERSTAND THIS IN ANY CAPACITY AND JUST WANTED TO MAKE THIS WORK AS OPPOSED TO LEARN HOW THIS WORKS
	OPENFILENAME Ofn;
	wchar_t FileName[MAX_PATH] = L"";

	ZeroMemory(&Ofn, sizeof(Ofn));
	Ofn.lStructSize = sizeof(Ofn);
	Ofn.hwndOwner = nullptr;
	Ofn.lpstrFile = FileName;
	Ofn.nMaxFile = MAX_PATH;
	Ofn.lpstrFilter = L"All Files\0*.*\0";
	Ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&Ofn))
	{
		const int BufferSize = WideCharToMultiByte(CP_UTF8, 0, FileName, -1, nullptr, 0, nullptr, nullptr);
		std::string Str(BufferSize, 0);
		WideCharToMultiByte(CP_UTF8, 0, FileName, -1, &Str[0], BufferSize, nullptr, nullptr);
		return Str;
	}
	return "";
}
std::vector<Node*> Level::highlightPath(Node* _end, bool _changeKey)
{
	std::vector<Node*> path;
	for (Node* node = _end; node != nullptr; node = node->m_parent)
	{
		node->updateColor(pathState);

		// Mark the key as 'p' for path — overwrite everything except walls
		if (_changeKey && node->m_key != 'w')
		{
			node->m_key = 'p';
		}

		path.push_back(node);
	}

	std::reverse(path.begin(), path.end());
	return path;
}
//---------------------------------------------------------//



//-------------------------GRAPH_SEARCHING-------------------------//
void Level::depthFirst()
{
	int collectedItems = 0;
	//only using .size() to keep it safe if something is loaded in thats not exact,
	//would look better with hardcoded numbers
	//std::vector<std::vector<bool>> checked(20, std::vector<bool>(20, false));
	std::vector<std::vector<bool>> checked(m_graphData.size(), std::vector<bool>(m_graphData[0].size(), false));
	depthFirstRecursive(m_startPos.x, m_startPos.y, checked, collectedItems);
}
bool Level::depthFirstRecursive(int _row, int _column, std::vector<std::vector<bool>>& _checked, int& _collected)
{
	//safety check 
	if (_checked[_row][_column])
	{
		return false;
	}

	//set first value to checked
	_checked[_row][_column] = true;
	m_graphData[_row][_column]->updateColor(openState);

#ifdef _DEBUG

	//debug the current node
	std::cout << "Current Node: " << m_graphData[_row][_column]->m_key << " at row: " << _row << ", column: " << _column << "\n";

#endif

	//check if Node is a key item
	if (m_graphData[_row][_column]->m_key >= 'a' && m_graphData[_row][_column]->m_key <= 'j')
	{
		std::cout << m_graphData[_row][_column]->m_key << " has been picked up\n";
		_collected++;

		//check if all itmes are collected and send return true pulse up the recursed chain.
		if (_collected >= 10)
		{
			m_graphData[_row][_column]->updateColor(closedState);
			std::cout << "All Items have been collected\n";
			return true;
		}
	}


	//iterate through each neighbour and recurse
	for (auto neighbour : m_graphData[_row][_column]->m_neighbours)
	{
		if (!_checked[neighbour->row][neighbour->column] && neighbour->m_key != 'x')
		{
			if (depthFirstRecursive(neighbour->row, neighbour->column, _checked, _collected))
			{
				m_graphData[_row][_column]->updateColor(closedState);
				return true;
			}
		}
	}

	//update state after finished with it.
	m_graphData[_row][_column]->updateColor(closedState);

	return false;
}
void Level::breadthFirst(Node* _start)
{
	std::queue<Node*> openQueue;
	std::vector<std::vector<bool>> checked(m_graphData.size(), std::vector<bool>(m_graphData[0].size(), false));
	int collected = 0;



	openQueue.push(_start);
	checked[_start->row][_start->column] = true;

	while (!openQueue.empty() && collected < 10)
	{
		Node* current = openQueue.front();
		openQueue.pop();


#ifdef _DEBUG	
		std::cout << "Current Node: " << m_graphData[current->row][current->column]->m_key 
				  << " at row: " << current->row 
				  << ", column: " << current->column 
				  << "\n";
#endif

		//check node value for item and check if all items have been picked up
		if (current->m_key >= 'a' && current->m_key <= 'j')
		{
			std::cout << current->m_key << " has been picked up\n";
			collected++;
			if (collected >= 10)
			{
				std::cout << "All Items have been collected\n";
				current->updateColor(closedState);
				break;
			}
		}

		current->updateColor(closedState);

		// sort neighbours to find smallest distance
		std::vector<Node*> sortedNeighbours = current->m_neighbours;
		std::sort(sortedNeighbours.begin(), sortedNeighbours.end(), distanceComparison(current, this));

		for (Node* neighbour : sortedNeighbours)
		{
			int row = neighbour->row;
			int column = neighbour->column;

			if (!checked[row][column] && neighbour->m_key != 'x')
			{
				checked[row][column] = true;
				neighbour->updateColor(openState);
				openQueue.push(neighbour);
				
			}
		}
	}
}
//-----------------------------------------------------------------//



//-------------------------A*_PATHFINDING-------------------------//
std::vector<Node*> Level::aStarPathfinding(Node* _start, Node* _end)
{
	//who to go to next
	std::priority_queue<Node*, std::vector<Node*>, fCostComparison> openList;

	//waiting to be visited
	std::set<Node*> openSet;
	
	//has been visited
	std::set<Node*> closedSet;

	_start->m_gCost = 0;
	_start->m_hCost = calculateHCost(_start, _end);
	_start->m_parent = nullptr;

	openList.push(_start);
	openSet.insert(_start);
	_start->updateColor(openState);

	while (!openList.empty())
	{
		Node* current = openList.top();
		openList.pop();
		openSet.erase(current);

		if (current == _end)
		{
			std::cout << "A* has returned a valid path" << std::endl;
			return highlightPath(_end, true);
		}
		
		closedSet.insert(current);
		current->updateColor(closedState);

		for (auto node : current->m_neighbours)
		{
			if (closedSet.find(node) != closedSet.end() || node->m_key == 'w')
				continue;

			float distanceCheck = euclideanDistance(current, node);
			//dont want a negative value here
			assert(distanceCheck > 0);

			 float updatedGCost = current->m_gCost + distanceCheck;

			if (updatedGCost < node->m_gCost)
			{
				node->m_parent = current;
				node->m_gCost = updatedGCost;
				node->m_hCost = calculateHCost(node, _end);

				if (openSet.find(node) == openSet.end())
				{
					openList.push(node);
					openSet.insert(node);
					node->updateColor(openState);

				}
			}
		}
	}

	std::cout << "A* has returned an invalid path" << std::endl;
	return {};
	//////////////////////////
}
void Level::saveAStarPath(std::string _filepath)
{
	std::ofstream saveFile(_filepath);
	if (!saveFile)
	{
		std::cerr << "Failed to open file for saving: " << _filepath << std::endl;
		return;
	}

	for (int row = 0; row < m_graphData.size(); row++)
	{
		for (int column = 0; column < m_graphData[row].size(); column++)
		{
			saveFile << m_graphData[row][column]->m_key;
		}
		saveFile << std::endl;
	}

	saveFile.close();
	std::cout << "Path saved and named: " << _filepath << std::endl;

}
//----------------------------------------------------------------//



//-------------------------BULLSHIT_SFML-------------------------//
void Level::bullshitPlayaroundColors()
//this was only for checking nodeState and checking colours (sanity check)
{
	
	NodeState stateApply = emptyState;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		stateApply = openState;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		stateApply = closedState;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		stateApply = pathState;
	}

	//only apply state instead of iterating the whole array every frame
	for (size_t row = 0; row < m_graphData.size(); row++)
	{
		for (size_t column = 0; column < m_graphData[row].size(); column++)
		{
			m_graphData[row][column]->updateColor(stateApply);
		}
	}
}
//---------------------------------------------------------------//
