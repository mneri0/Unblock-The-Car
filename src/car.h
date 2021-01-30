#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
#include <vector>

using namespace std;

// This class should only be used to help place blocks on the board with RUSHHOUR
// DO NOT USE IN MAIN
class Car{
	private:
		char num;
		size_t col, row; // Coordinates (column, row) left-most OR top-most
		char orientation; //To set orientation of car  use 'h'(horizontal) or 'v'(vertical) 
		size_t size; //Set as 2 for 2 block and 3 for 3 block car 
	public:
		// Default constructor creates the target object
		Car();
		//Type is 'C' for car and 'T' for truck
		Car(char type, size_t inX, size_t inY, char inOrien, char num);
		Car(const Car &source);
	
		//Get Functions
		char getOrien() const{return orientation;}
		size_t getCol() const{return col;}
		size_t getRow() const{return row;}
		size_t getSize() const{return size;}
		char getNum() const {return num;}

		//Set Functions
		void setCol(size_t inX){col = inX;}
		void setRow(size_t inY){row = inY;}

		//Overload Functions
		void operator=(const Car& source);
		bool operator==(const Car& source);
};

#endif
