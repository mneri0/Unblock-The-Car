#include "rushhour.h"

// Constructor automatically makes the target Car (the PLAYER car that is moved)
RushHour::RushHour(){
	Car target('C', 0, 2,'h','A');
	for(size_t i = 0; i < 6; i++){
		for(size_t j = 0; j < 6; j++)
			boardState[i][j] = ' ';
	}
	placeCar(target);
	pawns[0] = target;
	numCars = 1;
}

// Copy Constructor
RushHour::RushHour(const RushHour &source){
	numCars = source.numCars;
	for(size_t i = 0; i < 6; i++){
		for(size_t j = 0; j < 6; j++)
			boardState[i][j] = source.boardState[i][j];
	}
	for(size_t i = 0; i < 8; i++)
		pawns[i] = source.pawns[i];
}

// Destructor
RushHour::~RushHour(){
	delete []pawns;
}

// Prints out the board
void RushHour::printLot(){
	vector <string> colorS;

	//Ascii Colors
	string colorE="\033[0m";

		colorS.push_back("\033[21;37m");//White Underlined
		colorS.push_back("\033[1;31m");//Red
		colorS.push_back("\033[1;34m");//Blue
		colorS.push_back("\033[1;32m");//Green
		colorS.push_back("\033[1;33m");//Yellow
		colorS.push_back("\033[1;35m");//Magenta
		colorS.push_back("\033[1;36m");//Cyan
		colorS.push_back("\033[1;97m");//White
		


	cout << " _ _ _ _ _ _ _ _ _ _ _ _ " << endl;
	for(size_t i = 0; i < 6; i++){
		for(size_t j = 0; j < 6; j++){

			//Accepts lowercase and changes to uppercase letters
			switch(boardState[i][j]){
				case 'A':
				cout<< "|_" <<colorS[0]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'B':
				cout<< "|_" <<colorS[1]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'C':
				cout<< "|_" <<colorS[2]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'D':
				cout<< "|_" <<colorS[3]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'E':
				cout<< "|_" <<colorS[4]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'F':
				cout<< "|_" <<colorS[5]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'G':
				cout<< "|_" <<colorS[6]<<boardState[i][j]<<colorE<< "_";
				break;

				case 'H':
				cout<< "|_" <<colorS[7]<<boardState[i][j]<<colorE<< "_";
				break;

				default:
				cout<< "|_"<<boardState[i][j]<< "_";
				break;
			}
		}
		if(i != 2)
			cout << "|";
		cout << endl;
	}
}


// Determines if the direction (Either 'l', 'r', 'u', or 'd') is valid
// Assumes that the Car is already initiated with coordinates 
bool RushHour::isValid(Car &inMove, char inDir){
	if(inDir == 'l'){
		// Vertical Cars can't move left
		// Else, checks if the horizontal Car is on an edge and its left side to see if the spot is empty
		if(inMove.getOrien() == 'v'){
			return false;
		}
		else if(inMove.getOrien() == 'h'){
			if(inMove.getCol() == 0)
				return false;
			if(boardState[inMove.getRow()][inMove.getCol() - 1] != ' ')
				return false;
			return true;
		}
	}
	else if(inDir == 'r'){
		// Vertical Cars can't move right
		// Else, checks if the horizontal Car is on an edge and its right side to see if the spot is empty
		if(inMove.getOrien() == 'v'){
			return false;
		}
		else if(inMove.getOrien() == 'h'){
			if(inMove.getSize() == 2){
				if((inMove.getCol() + 2) > 5)
					return false;
				if(boardState[inMove.getRow()][inMove.getCol() + 2] != ' ')
					return false;
				return true;
			}
			else if(inMove.getSize() == 3){
				if((inMove.getCol() + 3) > 5)
					return false;
				if(boardState[inMove.getRow()][inMove.getCol() +3] != ' ')
					return false;
				return true;
			}
		}

	}
	else if(inDir == 'u'){
		// Horizontal Cars can't move up
		// Else, checks if the vertical Car is on an edge and its top side to see if the spot is empty
		if(inMove.getOrien() == 'h'){
			return false;
		}
		else if(inMove.getOrien() == 'v'){
                        if(inMove.getRow() == 0)
                                return false;
                        if(boardState[inMove.getRow() - 1][inMove.getCol()] != ' ')
                                return false;
                        return true;
		}
	}
	else if(inDir == 'd'){
		// Horizontal Cars can't move down
		// Else, checks if the vertical Car is on an edge and its bottom side to see if the spot is empty
		if(inMove.getOrien() == 'h'){
			return false;
		}
		else if(inMove.getOrien() == 'v'){
			if(inMove.getSize() == 2){
				if((inMove.getRow() + 2) > 5)
					return false;
				if(boardState[inMove.getRow() + 2][inMove.getCol()] != ' ')
					return false;
				return true;
			}
			else if(inMove.getSize() == 3){
				if((inMove.getRow() + 3) > 5)
					return false;
				if(boardState[inMove.getRow() + 3][inMove.getCol()] != ' ')
					return false;
				return true;	
			}
		}
	}
	
	// Invalid direction (letter)
	return false;
}

// Assumes the Car is a valid car and the direction is also valid
// Moves the Car on the board that is passed through
void RushHour::changeState(Car &inMove, char inDir){
	switch(inDir){
		case 'l':
			if(isValid(inMove, inDir))
				move(inMove, inDir);
			break;
		case 'r':
			if(isValid(inMove, inDir))
				move(inMove, inDir);
			break;
		case 'u':
			if(isValid(inMove, inDir))
				move(inMove, inDir);
			break;
		case 'd':
			if(isValid(inMove, inDir))
				move(inMove, inDir);
			break;
		default:
			break;
	}
}

// Places the Car on the board using its coordinates, size, and char(or num). Also assumes that all of the before mentioned traits have already 
// been initialized in the Car object.
void RushHour::placeCar(Car& car)
{
	if(car.getSize()==2)
	{
		if(car.getOrien()=='h')
		{
			boardState[car.getRow()][car.getCol()] = car.getNum();
			boardState[car.getRow()][car.getCol()+1] = car.getNum();		
		}
		if(car.getOrien()=='v')
		{
			boardState[car.getRow()][car.getCol()] = car.getNum();
			boardState[car.getRow()+1][car.getCol()] = car.getNum();
		}
	}


	if(car.getSize()==3) 
	{
		if(car.getOrien()=='h')
		{
			boardState[car.getRow()][car.getCol()] = car.getNum();
			boardState[car.getRow()][car.getCol()+1] = car.getNum();
			boardState[car.getRow()][car.getCol()+2] = car.getNum();
		}
		if(car.getOrien()=='v')
		{
			boardState[car.getRow()][car.getCol()] = car.getNum();
			boardState[car.getRow()+1][car.getCol()] = car.getNum();
			boardState[car.getRow()+2][car.getCol()] = car.getNum();
		}
	}

}

// Assumes the move is already VALID (look at changeState())
// NOTE: The coordinate of any vertical Car is the top-most block of its shape
// NOTE: The coordinate of any horizontal Car is the left-most block of its shape
// Makes the current coordinates into an empty block and then adds the block to which ever direction is called
void RushHour::move(Car &target, char inDir){
	if(target.getOrien() == 'h'){
		if(inDir == 'l'){
			if(target.getSize() == 2){
				boardState[target.getRow()][target.getCol() + 1] = ' ';
				boardState[target.getRow()][target.getCol() - 1] = target.getNum();
				target.setCol(target.getCol() - 1);			
			}
			else if(target.getSize() == 3){
				boardState[target.getRow()][target.getCol() + 2] = ' ';
				boardState[target.getRow()][target.getCol() - 1] = target.getNum();
				target.setCol(target.getCol() - 1);;
			}
		}
		else if(inDir == 'r'){
			if(target.getSize() == 2){
				boardState[target.getRow()][target.getCol()] = ' ';
				boardState[target.getRow()][target.getCol() + 2] = target.getNum();
				target.setCol(target.getCol() + 1);		
			}
			else if(target.getSize() == 3){
				boardState[target.getRow()][target.getCol()] = ' ';
				boardState[target.getRow()][target.getCol() + 3] = target.getNum();
				target.setCol(target.getCol() + 1);
			}
		}
	}
	else if(target.getOrien() == 'v'){
		if(inDir == 'u'){
			if(target.getSize() == 2){
				boardState[target.getRow() + 1][target.getCol()] = ' ';
				boardState[target.getRow() - 1][target.getCol()] = target.getNum();
				target.setRow(target.getRow() - 1);
			}
			else if(target.getSize() == 3){
				boardState[target.getRow() + 2][target.getCol()] = ' ';
				boardState[target.getRow() - 1][target.getCol()] = target.getNum();
				target.setRow(target.getRow() - 1);
			}
		}
		else if(inDir == 'd'){
			if(target.getSize() == 2){
				boardState[target.getRow()][target.getCol()] = ' ';
				boardState[target.getRow() + 2][target.getCol()] = target.getNum();
				target.setRow(target.getRow() + 1);
			}
			else if(target.getSize() == 3){
				boardState[target.getRow()][target.getCol()] = ' ';
				boardState[target.getRow() + 3][target.getCol()] = target.getNum();
				target.setRow(target.getRow() + 1);
			}
		}
	}

	return;
}

// Assumes the target Car is always the first Car object in the array of Cars(pawns[])
// Returns if the RushHour board is in a winning state
bool RushHour::checkWin(){
	if(pawns[0].getCol() == 4)
		return true;
		
	return false;
}

// Returns the Car at the ith position
Car RushHour::getPawn(size_t pos) const{
	assert(pos < numCars);	
	return pawns[pos];
}

// Resests the board's state and its Cars
void RushHour::resetBoard(){
	size_t count = 0;
	for(size_t i = 0; i < 6; i++){
		for(size_t j = 0; j < 6; j++)
			boardState[i][j] = ' ';
	}
	Car* empty = new Car[8];
	for(size_t i = 0; i < pawnsSize; i++)
		pawns[i] = empty[i];
}

// Takes in User input, accounts for lower and uppercase. Since this project uses a max of 8 blocks, the max letters are A-H.
void RushHour::userInput()
{
	size_t i=0;
	char name,dir;
	cin>>name>>dir;

	switch (name)
	{
	case 'a':
		name='A';
		break;

	case 'b':
		name='B';
		break;

	case 'c':
		name='C';
		break;

	case 'd':
		name='D';
		break;

	case 'e':
		name='E';
		break;

	case 'f':
		name='F';
		break;

	case 'g':
		name='G';
		break;

	case 'h':
		name='H';
		break;
	
	default:
		break;
	}

	while(name!=pawns[i].getNum() && i<pawnsSize)
	i++;

	if(i<pawnsSize)
	{
	changeState(pawns[i],dir);
	}
}

// Overloading = operator
void RushHour::operator=(const RushHour &source){
	numCars = source.numCars;
	for(size_t i = 0; i < 6; i++){
		for(size_t j = 0; j < 6; j++)
			boardState[i][j] = source.boardState[i][j];
	}
	for(size_t i = 0; i < 8; i++)
		pawns[i] = source.pawns[i];
}

// Important function to compare if the RushHour objects are the same, used heavily in the search algorithms
bool RushHour::operator==(const RushHour &source){
	if(!(numCars == source.numCars))
		return false;

	for(size_t i = 0; i < numCars; i++){
		if(!(pawns[i] == source.pawns[i]))
			return false;
	}

        for(size_t i = 0; i < 6; i++){
                for(size_t j = 0; j < 6; j++)
                        if(boardState[i][j] != source.boardState[i][j])
                                return false;
        }

	return true;
}

// This is TEST level for debugging purposes
void RushHour::levelTEST(){
	resetBoard();
	Car target;
	Car T1('C', 0, 0, 'h', 'B');
	pawns[0]=target;
	pawns[1]=T1;
	numCars = 2;
	placeCar(target);
	placeCar(T1);	

	// Use these lines to play the game yourself or set a limit to move the board to a certain state	
        while(checkWin() != true){
                userInput();
                printLot();
        }

}

// The following levels are pre-made solvable board problems
// NOTE: When creating a level make sure that the first car object is the target/player car
// Assumes that the RushHour boardState is empty (although we do have a reset board function)

void RushHour::levelA(){
	Car target;

	pawns[0]=target;
	
	placeCar(target);

	numCars = 1;

}

void RushHour::levelB(){
	Car target;
	Car t1('T', 3, 2, 'v', 'B');

	pawns[0] = target;
	pawns[1] = t1;

	placeCar(target);
	placeCar(t1);

	numCars = 2;
}

void RushHour::levelC(){
	Car target;
	Car c1('C', 2, 2, 'v', 'B');
	Car c2('C', 4, 2, 'v', 'C');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);

	numCars = 3;
}

void RushHour::levelD(){
	Car target;
	Car c1('C', 2, 3, 'v', 'B');
	Car c2('C', 3, 3, 'h', 'C');
	Car t1('T', 4, 0, 'v', 'D');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;
	pawns[3] = t1;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);
	placeCar(t1);

	numCars = 4;
} 

void RushHour::levelE(){
	Car target;
	Car c1('C', 3, 3, 'h', 'B');
	Car c2('C', 2, 4, 'h', 'C');
	Car t1('T', 2, 1, 'v', 'D');
	Car t2('T', 4, 0, 'v', 'E');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;
	pawns[3] = t1;
	pawns[4] = t2;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);
	placeCar(t1);
	placeCar(t2);

	numCars = 5;
}

void RushHour::levelF(){
	Car target;
	Car c1('C', 1, 4, 'v', 'B');
	Car c2('C', 2, 4, 'h', 'C');
	Car c3('C', 4, 3, 'v', 'D');
	Car t1('T', 3, 0, 'v', 'E');
	Car t2('T', 5, 3, 'v', 'F');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;
	pawns[3] = c3;
	pawns[4] = t1;
	pawns[5] = t2;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);
	placeCar(c3);
	placeCar(t1);
	placeCar(t2);
	
	numCars = 6;
}

// BFS takes a few seconds for this one 
void RushHour::levelG(){
	Car target;
	Car c1('C', 1, 4, 'h', 'B');
	Car c2('C', 4, 4, 'h', 'C');
	Car c3('C', 4, 5, 'h', 'D');
	Car c4('C', 3, 4, 'v', 'E');
	Car t1('T', 1, 3, 'h', 'F');
	Car t2('T', 5, 0, 'v', 'G');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;
	pawns[3] = c3;
	pawns[4] = c4;
	pawns[5] = t1;
	pawns[6] = t2;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);
	placeCar(c3);
	placeCar(c4);
	placeCar(t1);
	placeCar(t2);

	numCars = 7;
}

void RushHour::levelH(){
	Car target;
	Car c1('C', 0, 0, 'v', 'B');
	Car c2('C', 2, 2, 'v', 'C');
	Car c3('C', 0, 3, 'h', 'D');
	Car c4('C', 4, 4, 'h', 'E');
	Car t1('T', 3, 2, 'v', 'F');
	Car t2('T', 5, 0, 'v', 'G');
	Car t3('T', 1, 1, 'h', 'H');

	pawns[0] = target;
	pawns[1] = c1;
	pawns[2] = c2;
	pawns[3] = c3;
	pawns[4] = c4;
	pawns[5] = t1;
	pawns[6] = t2;
	pawns[7] = t3;

	placeCar(target);
	placeCar(c1);
	placeCar(c2);
	placeCar(c3);
	placeCar(c4);
	placeCar(t1);
	placeCar(t2);
	placeCar(t3);

	numCars = 8;

}
