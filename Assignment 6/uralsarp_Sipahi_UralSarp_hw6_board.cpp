#include "uralsarp_Sipahi_UralSarp_hw6_board.h"

using namespace std;

template <class itemType>
Board<itemType>::Board(int rows, int columns) //board constructor
{
	row=rows;
	column=columns;

	board=new Card<itemType>*[row];  //initialization of the board
	for (int i=0; i<row; i++){
		board[i]=new Card<itemType>[column];
	}
	
}

template <class itemType>
Board<itemType>::~Board(){ //destructor for board

	for (int x=0; x<row; x++){
		delete[] board[x];
    }
	delete[] board;
}

template <class itemType>
void Board<itemType>::readBoardFromFile(ifstream & input){
	int rowplace=0;
	int columnplace=0;
	string line;
	itemType val;
	while (getline(input,line)){ // this part puts the input into the board and fills it.
		istringstream strstream(line);
		while (rowplace<row && columnplace<column){
			strstream>>val;
			board[rowplace][columnplace].value=val;
			board[rowplace][columnplace].closed=true;
			columnplace++;
		}
		rowplace++;
		columnplace=0;
	}
}


template <class itemType>
void Board<itemType> :: displayBoard(){
	for (int i=0; i<row; i++){
		for (int j=0; j<column; j++){
			if (board[i][j].closed==true){
				cout<<"X"<<" ";
			}
			else{
				cout<<board[i][j].value<<" ";
			}			
		}
		cout<<endl;
	}
}

template <class itemType>
void Board<itemType>::closeCard(int rowplace, int columnplace){

	board[rowplace][columnplace].closed=true;
}

template <class itemType>
int Board<itemType>::getRow(){
	return row;
}

template <class itemType>
int Board<itemType>::getColumn(){
	return column;
}

template <class itemType>
itemType Board<itemType>::getValue(int rowindex, int columnindex){
	return board[rowindex][columnindex].value;
}

template <class itemType>
bool Board<itemType>::getClosed(int rowindex, int columnindex){
	return board[rowindex][columnindex].closed;
}

template <class itemType>
void Board<itemType>::open(int rowindex, int columnindex){
	board[rowindex][columnindex].closed=false;
}