//===========================================================================
//== Bachelor of Software Engineering									   ==
//== Media Design School												   ==
//== Auckland															   ==
//== New Zealand														   ==
//== (c)																   ==
//== 2025 Media Design School											   ==
//== File Name : main.cpp												   ==
//== Description : the main loop yeah yeah                                 ==
//== Author : Logan Jones												   ==
//== Mail : logan.jones@mds.ac.nz										   ==
//===========================================================================/


#include "Level.h"
#include "Button.h"


int main()
{
    //window
    sf::RenderWindow window(sf::VideoMode({ 1200, 1000 }), "A* Pathfinding");

    Button depthFirstButton(1025, 100, "Depth First Search");
    Button breadthFirstButton(1025, 150 + 25, "Breadth First Search");
    Button aStarPathfindingButton(1025, 200 + 50, "A* Pathfinding");
    Button saveAStarPath(1025, 250 + 75, "Save A* Path");
    Button resetLevelButton(1025, 300 + 100, "Reset Level");
    Button dialogueButton(1025, 350 + 125, "Open File Window");

    //Level object
    Level newLevel;     


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (depthFirstButton.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.setLevel();

                    newLevel.depthFirst();
                }

                if (breadthFirstButton.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.setLevel();

                    newLevel.breadthFirst(newLevel.getStart());
                }

                if (aStarPathfindingButton.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.setLevel();

                    newLevel.aStarPathfinding(newLevel.getStart(), newLevel.getEnd());
                }

                if (resetLevelButton.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.setLevel();
                }

                if (dialogueButton.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.loadLevel(newLevel.openFileDialog());
                    newLevel.setLevel();
                }

                if (saveAStarPath.m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    newLevel.unloadLevel();
                    newLevel.setLevel();

                    newLevel.aStarPathfinding(newLevel.getStart(), newLevel.getEnd());
                    newLevel.saveFileDialog();
                    //newLevel.saveAStarPath("A Star Path Map.txt");
                }

            }
        }

        breadthFirstButton.updateButton(window);
        depthFirstButton.updateButton(window);  
        aStarPathfindingButton.updateButton(window);
        resetLevelButton.updateButton(window);
        dialogueButton.updateButton(window);
        saveAStarPath.updateButton(window);

#ifdef _DEBUG

        //some bullshit to play around with to make sure colors are changing appropriately
        //Press A for "open" color
        //Press S for "closed" color
        //Press D for "path" color
        //newLevel.bullshitPlayaroundColors();

#endif //_DEBUG


        window.clear();

        //Loop for priting the raw shape data instead of the background sprite
        for (int i = 0; i < newLevel.m_graphData.size(); i++)
        {
            for (int j = 0; j < newLevel.m_graphData[i].size(); j++)
            {
                if (newLevel.m_graphData[i][j] != nullptr)
                {
                    window.draw(newLevel.m_graphData[i][j]->m_shape);
                    window.draw(newLevel.m_graphData[i][j]->m_text);

                }
            }
        }

        //could this be put into a vector of buttons and iterated through?
        //yes, but effort 
        window.draw(depthFirstButton.m_shape);
        window.draw(depthFirstButton.m_text);

        window.draw(breadthFirstButton.m_shape);
        window.draw(breadthFirstButton.m_text);

        window.draw(aStarPathfindingButton.m_shape);
        window.draw(aStarPathfindingButton.m_text);

        window.draw(resetLevelButton.m_shape);
        window.draw(resetLevelButton.m_text);

        window.draw(dialogueButton.m_shape);
        window.draw(dialogueButton.m_text);

        window.draw(saveAStarPath.m_shape);
        window.draw(saveAStarPath.m_text);


        window.display();
    }
}