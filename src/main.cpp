#include <iostream>
#include "car.h"
#include "rushhour.h"
#include "tNode.h"


using namespace std;

int main(){
				
	RushHour board;
	board.levelH();
	tNode* tree = new tNode;	
	tree->setData(board);
	cout << "STARTING BOARD\n";	
	tree->printData();
	
	size_t movesTaken = 0;
	tNode* tSOLUTION = new tNode;	

	tSOLUTION = tree->BFS(tree);	
	tSOLUTION->countMoves(tSOLUTION, movesTaken);
	cout << "MOVES TAKEN: " << movesTaken << endl;
	tSOLUTION->printTree(tSOLUTION);

/* 	movesTaken = 0;	
	tSOLUTION = tree->DFS(tree);	
    tSOLUTION->countMoves(tSOLUTION, movesTaken);
    cout << "MOVES TAKEN: " << movesTaken << endl; 
	tSOLUTION->printTree(tSOLUTION);

	movesTaken = 0;	
	tSOLUTION = tree->IDDFS(tree, 2000);	
	tSOLUTION->countMoves(tSOLUTION, movesTaken);
    cout << "MOVES TAKEN: " << movesTaken << endl; 
	tSOLUTION->printTree(tSOLUTION);
	
	movesTaken = 0;	
	tSOLUTION = tree->bStar(tree);
	tSOLUTION->countMoves(tSOLUTION, movesTaken);
    cout << "MOVES TAKEN: " << movesTaken << endl;
	tSOLUTION->printTree(tSOLUTION); */
		
}
