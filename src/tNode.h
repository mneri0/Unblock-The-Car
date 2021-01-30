#ifndef __TNODE_H__ 
#define __TNODE_H__

#include <iostream>
#include <cassert>
#include "rushhour.h"
#include <stack>
#include <queue>

using namespace std;

class tNode {
    private:
    RushHour data; //Stores gamestate as rushhour data type
    tNode* parent; //Points to parent
    tNode** children; //points to children
    size_t numChildren;//Stores the number of children
    const size_t capChildren = 16; //Total capacity of children

    public:
    //Constructors
    tNode();
    tNode(const RushHour& copy);
    tNode(const tNode& source);
    ~tNode();
    
    //Get functions
    tNode* getChild(size_t pos) const; //Get the ith child one fro  all children
    tNode** getChildren() const; // Returns pointer of children
    size_t getNumChildren(){return numChildren;} const
    RushHour getData(){return data;} void printData(){data.printLot();}
    
    //Set functions
    void setChild(RushHour &inData,size_t pos); //To set ith children to a different state
    void addChild(RushHour &inData); // Adds children to a node
    void genChildren(); //Uses addChild to to generate child
    void setData(RushHour& source){data = source;}

    //Deletes Tree Function
    void freeTree(tNode* root);

    //Member Functions
    void printTree(tNode* root);//Prints the tree
    void countMoves(tNode* root, size_t &count);//Counts the number of moves

    //Overload Functions
    bool operator==(const tNode*& source);
    bool operator<(const tNode*& source);

    //Seatching Algorithms Functions

    tNode* BFS(tNode* state); //Breadth First Search - Use Queue
    tNode* DFS(tNode* state); //Depth First Search - Use Stack 
    tNode* IDDFS(tNode* state, size_t maxLimit); //Iterative Deepening Depth First Search
    bool DLS(tNode*& trace, tNode* target, size_t limit, stack<tNode*>& prev, stack<tNode*>& fin, size_t& nodes); //Depth Limited Search for IDDFS
    tNode* bStar(tNode* state); //B* (Best First Search)

};

    
#endif
