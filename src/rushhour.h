#ifndef __RUSH_HOUR_H__
#define __RUSH_HOUR_H__

#include <iostream>
#include <vector>
#include <cassert>
#include "car.h"

using namespace std;

class RushHour{

    private:
	char boardState[6][6];
	Car* pawns = new Car[8];
	size_t pawnsSize = 8;
	size_t numCars;

    public:
    	RushHour();
	RushHour(const RushHour &source);
	~RushHour();
	
	//Function to print out the boardState (All different cars will have different colors)
	void printLot();

	//Function to add Cars, Trucks, and Target onto the gameBoard
	void placeCar(Car& car);

	// Changes the boardState using a Car object and its direction
	void changeState(Car &inMove, char inDir);

	// Function to check if move is valid
	bool isValid(Car &inMove, char inDir);

	// Moves the objects on the gameBoard/boardState
	void move(Car &target, char inDir);

	// Win State - Checks for the 'player' car
	bool checkWin(); 
	
	// Get functions
	Car* getPawns() {return pawns;}
	Car getPawn(size_t pos) const;
	size_t getNumCars() const {return numCars;}

	// Set Functions
	void setPawns(Car*& inPawns) {pawns = inPawns;}
	void setPawn(Car& inPawn, size_t pos) {pawns[pos] = inPawn;}
	void setNumCars(size_t inNum) {numCars = inNum;}

	// Reset Board Function
	void resetBoard();

	// Function to input move from user
	void userInput();

	// LEVELS
	void levelTEST();
	void levelA();
	void levelB();
	void levelC();
	void levelD();
	void levelE();
	void levelF();
	void levelG();
	void levelH();

	// Overloading Operators
	void operator=(const RushHour &source);
	bool operator==(const RushHour &source);
};

#endif 
