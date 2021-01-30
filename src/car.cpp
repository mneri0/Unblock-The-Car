#include "car.h"

// Constructor that initializes the target/player Car
Car::Car(){
        size = 2;
        col = 0;
        row = 2;
        orientation = 'h';
        num='A';
}

// Overloaded Constructor
// Input: the type of car ('C' for car or 'T' for truck), its x-y coordinates, 
// 	its orientation ('h' for horizontal or 'v' for vertical),  and the letter/num 
// NOTE: When setting its x-y coordinates, if it is ('h')horizontal make sure to enter its left-most coordinates
// 	if it is ('v')vertical make sure to enter its top-most coordinates
Car::Car(char type, size_t inX, size_t inY, char inOrien, char inNum){
        if(type == 'C'){
                col = inX;
                row = inY;
                orientation = inOrien;
                size = 2;
                num=inNum;
        }
        else if(type == 'T'){
                col = inX;
                row = inY;
                orientation = inOrien;
                size = 3;
                num=inNum;
        }
}

// Copy Constructor
Car::Car(const Car &source){
        col = source.col;
        row = source.row;
        orientation = source.orientation;
        size = source.size;
        num = source.num;
}

// Copy Car object
void Car::operator=(const Car& source){
	num = source.num;
	col = source.col;
	row = source.row;
	orientation = source.orientation;
	size = source.size;
}

// Overloading == operator
bool Car::operator==(const Car& source){
	if((col == source.col) && (row == row))
		if(orientation == source.orientation)
			if(size == source.size)
				return true;
	return false;
}
