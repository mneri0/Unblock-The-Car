Rush Hour

RushHour is a video game first developed by clockwork entertainment for playstation and windows with a high-level, top-down view of the cars and tracks based on a sliding block puzzle game invented by Nob Yoshigahara in the 1970s. The aim of this game is to find a path for the players car out of the parking lot by removing all the obstacles blocking the exit.

To run the game download the  rushhour/src
There are a total of 7 files:
1. car.h
2. car.cpp
3. rushhour.h
4. rushhour.cpp
5. tNode.h
6. tNode.cpp
7. main.cpp

Compile the game by typing: $make

To try out different levels call Level_() where the underscore can be replaced by A-H

Example: 

RushHour some_name;

some_name.levelA();


To try different board configurations edit levelTEST() in "rushhour.cpp"

Create cars in the levelTEST()

Make sure to follow the Car constructor parameters as stated in "car.cpp"

Then add them to the pawns[] array

Then use placeCar() function to place on board

Record the number of cars on the board (current max is 8)

Call the changeState function for movement

After making the changes, make a tNode like this: tNode* nameHere = new node;

Set the data of the tNode to the RushHour you created: nameHere->setData(some_name);

Then use any search function!

For more examples look at "main.cpp"

That's it! Thanks for reading!
