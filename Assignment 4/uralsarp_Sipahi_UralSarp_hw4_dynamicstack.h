#include <iostream>


struct cellStruct{
	char num;
	bool check;
};

struct Position 
{
	int row, col; //Identifies position of a specific cell, Position(0,0) -> top left corner of the board
	Position(int x_ = 0, int y_ = 0) : row(x_), col(y_) {};
};

struct StackNode 
{
	
	Position pos; //When backtracking this value gives the position of the current place
	StackNode *next;
	StackNode(Position p = Position(), StackNode* n = NULL) :pos(p), next(n) {};
};


class dynamicstack
{
private:
	StackNode *top;

public:
	dynamicstack(void); //constructor
	~dynamicstack(); //destructor
	void push(StackNode);
	void pop(StackNode&);
	bool isEmpty(void);
};
