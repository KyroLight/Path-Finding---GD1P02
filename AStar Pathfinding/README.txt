Few things to note:

---------------------------------------

The GUI will show the visual output but please refer to the console output to show the neccessary information

---------------------------------------

the file dialog was taken from:

https://answers.microsoft.com/en-us/windows/forum/all/the-functionality-for-opening-a-file-dialog-box/c9521601-8f0b-4114-9c6c-729719e3d964

I then used Ai to make it function, I have no intention to learn how it works at the moment or understand it at all which is why I did this.

---------------------------------------

Sometimes my buttons will give the wrong thing, or when I load in a new map it will auto complete the A* pathfinding and saving? still confuses me.

---------------------------------------

My SFML in main is terrible yes, using SFML was a mistake, as nothing needs to be displayed so I just made it harder on myself for what reason? idk.

---------------------------------------

When launching the program, it will default to showing nothing really and the graph data is filled with '.' or empty Nodes,
so A* pathfinding will return a true value, because the start and end node are placed in the same place, and the depth and breadth search will fill the table.
This is not correct but I was struggling to find a way around loading nullptrs in while still displaying something, so my solution was to fill it with junk.

---------------------------------------





Formal Requirements:

1. The program shall incrementally display the steps taken by the computer, providing the user with a clear sense
   of progression and satisfaction.

2. The program shall update the colour of each node to visually represent its current state.

3. The program shall be designed with scalability and maintainability in mind to ensure long-term adaptability.

4. The program shall include comprehensive testing to ensure that individual units and methods
   function correctly and error-prone.
