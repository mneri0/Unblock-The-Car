#include "tNode.h"

tNode::tNode(){
	// The initial boardState is created when we call a level and set its data
	tNode* parent = NULL;
	numChildren = 0;
	children = new tNode*[capChildren];
	for(size_t i = 0; i < capChildren; i++)
		children[i] = NULL;
}

// Create a tNode object with the RushHour object already initialized 
tNode::tNode(const RushHour& copy){
	tNode* parent = NULL;
	numChildren = 0;
	data = copy;
	children = new tNode*[capChildren];
	for(size_t i = 0; i < capChildren; i++)
		children[i] = NULL;	
}

// Copy Constructor
tNode::tNode(const tNode& source){
	tNode* parent = source.parent;
	data = source.data;
	numChildren = source.numChildren;
	children = new tNode*[capChildren];
	for(size_t i = 0; i < capChildren; i++)
		children[i] = source.children[i];	
}

// Destructor
tNode::~tNode(){
	tNode* parent = NULL;
	numChildren = 0;
	for(size_t i = 0; i < capChildren; i++)
		delete children[i];
	delete []children;
}

// Returns the child at the ith position
tNode* tNode::getChild(size_t pos) const{
	assert(pos < capChildren);
	return this->children[pos];
}

// Returns a pointer** containing all the node's children
tNode** tNode::getChildren() const{
	return children;
}

// Changes the ith child's RushHour data 
void tNode::setChild(RushHour &inData, size_t pos){
	assert(pos < numChildren);
	for(size_t i = 0; i <= pos; i++)
		children[i]->data = inData;
}

// Adds a child expecting a filled RushHour data
// This is used in genChildren only
void tNode::addChild(RushHour &inData){
	assert(numChildren < capChildren);
	tNode* insert;
	insert = new tNode;
	insert->data = inData;
	insert->parent = this;
	children[numChildren++] = insert;
}

// Generates children based on the numbers of cars on the board so there will bea total of n * 2 moves
// DOES NOT CHECK FOR REPEATS, checking occurs in the searches
// Assumes that there is enough space to generate children 
void tNode::genChildren(){
	
	// Copying cars from the node in order to create new boards with the same amount of cars with their coordinates
	Car* blocks = new Car[8];
	size_t numCars = this->data.getNumCars();
	for(size_t i = 0; i < numCars; i++){
		blocks[i] = this->data.getPawn(i);
	}

	RushHour move1, move2;

	// For each car we create 2 new moves. If it is a vertical Car we make 2 moves (one for up and one for down)
	// Vice versa for horizontal cars (one for left and one for right)
	for(size_t i = 0; i < numCars; i++){	
		move1 = this->data;
		move2 = this->data;
		if(blocks[i].getOrien() == 'v'){
                        move1.changeState(blocks[i], 'u');
			move1.setPawn(blocks[i], i);
			blocks[i] = this->data.getPawn(i);
                        move2.changeState(blocks[i], 'd');
			move2.setPawn(blocks[i], i);
                        this->addChild(move1);
                        this->addChild(move2);	
		}
		else if(blocks[i].getOrien() == 'h'){
                        move1.changeState(blocks[i], 'r');
			move1.setPawn(blocks[i], i);
			blocks[i] = this->data.getPawn(i);
                        move2.changeState(blocks[i], 'l');
			move2.setPawn(blocks[i], i);
                        this->addChild(move1);
                        this->addChild(move2);
		}
	}
}

// Frees up the memory of the tree, enables reusing tNode pointers in searches
void tNode::freeTree(tNode* root){
	if(root == NULL)
		return;
	for(size_t i = 0; i < numChildren; i++)
		freeTree(root->children[i]);
	free(root);	
}

// Prints out the solution or the path of the tNode from it's solution to the beginning state
// Assumes that the tNode passed through the parameters is the solution board
void tNode::printTree(tNode* root){
	if(root == NULL)
		return;
	root->data.printLot();

	printTree(root->parent);
}

// Counts the number of moves taken to solve the board
// Assumes the tNode passed through is the solution node
// We subtract 1 because the starting root is counted and it is technically not a move
void tNode::countMoves(tNode* root, size_t& count){
	if(root == NULL){
		count--;	
		return;
	}
	count++;

	countMoves(root->parent, count);
}

// For comparing tNode's data and check if it is a repeat; a main component in the searches
bool tNode::operator==(const tNode*& source){
	if(this->data == source->data)
		return true;
	return false;
}

// ONLY TO BE USED WITH B* SEARCH (PriorityQueue uses this overload)
bool tNode::operator<(const tNode*& source){
	Car thisCar, thatCar;
	thisCar = this->data.getPawn(0);
	thatCar = source->data.getPawn(0);

	// Checks and Compares the distance from their position to the goal
	// 4 is the maximum column the target can get to. The target Car is always takes up 2 blocks 
	if((4 - thisCar.getCol()) < (4 - thatCar.getCol()))
		return true;
	return false;	
}

// Assumes the starting state has a SOLUTION and returns the SOLUTION tNode
tNode* tNode::BFS(tNode* state){
	// Deletes tNode's previous data, we set children to NULL for safety
	for(size_t i = 0; i < state->numChildren; i++){
		freeTree(state->children[i]);
		state->children[i] = NULL;
        }
	state->numChildren = 0;
	
	queue <tNode*> Q;
	queue <tNode*> prev;
	queue <tNode*> fin;
	bool isRepeat = false;
	size_t nodes = 0;
	tNode* curr = new tNode;
	Q.push(state);

	while (!Q.empty() && !(curr->data.checkWin())){
		nodes++;
		curr = Q.front();
		Q.pop();	
		curr->genChildren();	
		
		// Looking at generated children of current node
		for(size_t i = 0; i < curr->numChildren; i++){

			// Checking for duplicates so that we don't push it in the queue
			while(!prev.empty()){
				if(curr->children[i]->data == prev.front()->data){
					isRepeat = true;
				}
				if(curr->data == prev.front()->data){
					isRepeat = true;
				}
				fin.push(prev.front());
				prev.pop();
			}
			
			while(!fin.empty()){
                        	prev.push(fin.front());
                        	fin.pop();
			}

			if(curr->data == curr->children[i]->data){
				isRepeat = true;
			}
			if(!isRepeat){
				Q.push(curr->children[i]);
			}
			isRepeat = false;
		}
		// Finished looking at node, we push it in prev 
		prev.push(curr);
	}

	cout << "_____________________________________\n\n";
        cout << "BFS EXAMPLE\n";
	curr->data.printLot();
	cout << "WINNING STATE! \n";	
	cout << "NODES VISTED: " << nodes << endl;	
	
	return curr;	
}

// Assumes the starting state has a SOLUTION and returns the SOLUTION tNode
tNode* tNode::DFS(tNode* state){
	// Deletes tNode's previous data, we set children to NULL for safety
	for(size_t i = 0; i < state->numChildren; i++){
		freeTree(state->children[i]);
		state->children[i] = NULL;
	}
	state->numChildren = 0;
	
	stack <tNode*> S;
	stack <tNode*> prev;
	stack <tNode*> fin;
	bool isRepeat = false;
	size_t nodes = 0;
	tNode* curr = new tNode;
	S.push(state);

	while (!S.empty() && !(curr->data.checkWin())){
		nodes++;
		curr = S.top();
		S.pop();
		curr->genChildren();
		
		// Looking at generated children of current node
		for(size_t i = 0; i < curr->numChildren; i++){	
			// Checking for duplicates so that we don't push it in the queue
			while(!prev.empty()){
				if(curr->children[i]->data == prev.top()->data){
					isRepeat = true;
				}
				if(curr->data == prev.top()->data)
					isRepeat = true;
				fin.push(prev.top());
				prev.pop();
			}
			while(!fin.empty()){
				prev.push(fin.top());
				fin.pop();
			}
			if(curr->data == curr->children[i]->data){
				isRepeat = true;
			}
			if(!isRepeat){
				S.push(curr->children[i]);
			}
			isRepeat = false;
		}
		// Finished looking at node, we push it in prev 
		prev.push(curr);
	}

        cout << "_____________________________________\n\n";
        cout << "DFS EXAMPLE\n";
        curr->data.printLot();
	cout << "WINNING STATE! \n";	
	cout << "NODES VISTED: " << nodes << endl;	

	return curr;	
}

// Assumes the starting state has a SOLUTION and returns the SOLUTION tNode
tNode* tNode::IDDFS(tNode* state, size_t maxLimit){
	// Deletes tNode's previous data, we set children to NULL for safety
	for(size_t i = 0; i < state->numChildren; i++){
		freeTree(state->children[i]);
		state->children[i] = NULL;
	}
	state->numChildren = 0;
       
       	// Use stack to store duplicates
	stack <tNode*> prev;
        stack <tNode*> fin;
        size_t nodes = 0;
	
        tNode* curr = new tNode;
	tNode* trace; // To keep track of the final solution

	// MaxLimit loop to simulate BFS algorithm
        for(size_t depth = 0; depth <= maxLimit; depth++){
		curr = state;
		// Pass in stacks to preserve the repeated nodes
		// Pass in nodes to count nodes traversed through
		// Pass in curr for the starting state
		if(DLS(trace, curr, depth, prev, fin, nodes) == true){
        		cout << "_____________________________________\n\n";
		        cout << "IDDFS EXAMPLE\n";
        		trace->data.printLot();
        		cout << "WINNING STATE! \n";
        		cout << "NODES VISTED: " << nodes << endl;

        		return trace;
		}

		// Empty out the previously searched through nodes because at the 2nd depth it will not generate anymore children
		if(!prev.empty())
			prev.pop();
		if(!fin.empty())
			fin.pop();
		
		// Delete tree so that the genChildren doesn't overflow the num of children state has		
		for(size_t i = 0; i < state->numChildren; i++){
			freeTree(state->children[i]);
			state->children[i] = NULL;
		}
		state->numChildren = 0;
	}

	// Just in case the depth passed through main for IDDFS wasn't enough to find a solution 	
	return NULL;
}

// Recursively defined DFS algorithm. Stacks are passed by reference so that we can keep adding previously visited nodes. Trace is also passed by reference
// to record the winning state's path.
// We end at the winning state or if the limit passed through from IDDFS has reached to zero
bool tNode::DLS(tNode*& trace, tNode* target, size_t limit, stack<tNode*>& prev, stack<tNode*>& fin, size_t& nodes){
	nodes++;	
	if(target->data.checkWin() == true){
		trace = target;	
		return true;
	}
	if(limit <= 0)
		return false;

	bool isRepeat = false;	


	// Checking for duplicates so that we don't recursively search nodes already looked at to save speed and prevent infinite loops
        while(!prev.empty()){
		if(target->data == prev.top()->data)
			isRepeat = true;
		fin.push(prev.top());
		prev.pop();
	}
	while(!fin.empty()){
		prev.push(fin.top());
		fin.pop();
	}

	// Checks if parent is NULL because of the 1st depth (ROOT node always has a parent of NULL)
	if((target->parent != NULL) && (target->data == target->parent->data))
		isRepeat = true;
	if(!isRepeat){
		// Generates children and searches them in a stack-like way
		prev.push(target);
		target->genChildren();
		for(size_t i = 0; i < target->numChildren; i++){
			if(DLS(trace, target->children[i], limit - 1, prev, fin, nodes) == true) // We go down one depth until we reach 0
				return true;		
		}	
	}

	// If this is reached then the node was a repeat
	return false;	
}

// Assumes the starting state has a SOLUTION and returns the SOLUTION tNode
// Works exactly like the BFS algorithm except that it uses a priority queue to determine which node gets pushed in.
// Overloaded the operator < so that priority_queue can check the "score" (look at operator< for more info)
tNode* tNode::bStar(tNode* state){	
	// Deletes tNode's previous data, we set children to NULL for safety
	for(size_t i = 0; i < state->numChildren; i++){
		freeTree(state->children[i]);
		state->children[i] = NULL;
	}
	state->numChildren = 0;

        priority_queue<tNode*> Q;
        queue<tNode*> prev;
      	queue<tNode*> fin;
        bool isRepeat = false;
        size_t nodes = 0;
        tNode* curr = new tNode;
        Q.push(state);

        while (!Q.empty() && !(curr->data.checkWin())){
                nodes++;
                curr = Q.top();
                Q.pop();
                curr->genChildren();

		// Looking at generated children of current node
                for(size_t i = 0; i < curr->numChildren; i++){
			// Checking for duplicates so that we don't push it in the queue
                        while(!prev.empty()){
                                if(curr->children[i]->data == prev.front()->data){
                                        isRepeat = true;
                                }
                                if(curr->data == prev.front()->data){
                                        isRepeat = true;
                                }
                                fin.push(prev.front());
                                prev.pop();
                        }

                        while(!fin.empty()){
                                prev.push(fin.front());
                                fin.pop();
                        }

                        if(curr->data == curr->children[i]->data){
                                isRepeat = true;
                        }
                        if(!isRepeat){
                                Q.push(curr->children[i]);
                        }
                        isRepeat = false;
                }
		// Finished looking at node, we push it in prev 
                prev.push(curr);
        }

        cout << "_____________________________________\n\n";
        cout << "B* EXAMPLE\n";
        curr->data.printLot();
        cout << "WINNING STATE! \n";
        cout << "NODES VISTED: " << nodes << endl;

	return curr;
}
