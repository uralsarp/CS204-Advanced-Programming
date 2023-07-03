#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

template <class itemType>
struct Card{
	itemType value;
	bool closed;
};



template <class itemType>
class Board{
	public:
		Board(int row,int column); //constructor
		~Board(); //destructor
		void readBoardFromFile(ifstream &); //read file into the board
		void displayBoard(); //display the board
		void closeCard(int row, int column); //close the corresponding card in the board
		int getRow(); //return the row of the board
		int getColumn(); //return the column of the board

		void open(int rowindex,int columnindex); //open the card with the corresponding indexes
		itemType getValue(int rowindex,int columnindex); //return the value of the card with the corresponding indexes
		bool getClosed(int rowindex,int columnindex); //check if the card is closed or not


	private:
		int row;
		int column;
		Card<itemType> **board;
	
};

	

#include "uralsarp_Sipahi_UralSarp_hw6_board.cpp"
#endif

