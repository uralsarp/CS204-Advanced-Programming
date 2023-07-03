#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "uralsarp_Sipahi_UralSarp_hw4_dynamicstack.h"

using namespace std;


void printMat(cellStruct **board,int row, int column){

	 for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
			cout <<  board[i][j].num << " ";
        cout << "\n";
    }


}
bool match(cellStruct **board, int &row1, int &column1, string bit, int &wordcheck, int row, int column,bool &columnchange, bool &rowchange){
	if ((column1+1<column) && (board[row1][column1+1].num==bit.at(wordcheck)) && (board[row1][column1+1].check==false)){
		column1++;
		wordcheck++;
		columnchange=true; //if the column value is changed change it to true.
		rowchange=false;
		return true;
	}
	else if ((row1+1<row) && (board[row1+1][column1].num==bit.at(wordcheck)) && (board[row1+1][column1].check==false)){
		row1++;
		wordcheck++;
		rowchange=true; //if the row value is changed change it to true.
		columnchange=false;
		return true;
	}
	else{
		return false;
	}
}
void print(dynamicstack &myStack, string bit){
	dynamicstack tempStack;
	while (!myStack.isEmpty()){ //pop from onestack push to another
		StackNode temp;
		myStack.pop(temp);
		tempStack.push(temp);
	}
	cout<<"The bit string "<<bit<<" is found following these cells: "<<endl;
	while (!tempStack.isEmpty()){ //print the pushed stack
		StackNode temp1;
		tempStack.pop(temp1);
		cout<<"("<<temp1.pos.row<<","<<temp1.pos.col<<")"<<" ";
	}
	


}
void solve(cellStruct **board, int row, int column, dynamicstack &myStack,string bit){
	bool wordplaced=true;
	
	if (board[0][0].num!=bit.at(0)){ //if the top left corner value doesnt match with the strings first char, dont need to check the other ones.
		wordplaced=false;
		board[0][0].check=true;
	}
	else{
		StackNode temp;
		int row1 = 0;
		int column1 = 0; // row and column values to search the board.
		int wordcheck = 1; //counter to go over the string char by char
		myStack.push(StackNode(Position(0,0)));
		bool rowchange=false; //check if the row value is changed
		bool columnchange=false; //check if the column value is changed

		while (wordcheck<bit.length() && row1<row){
			if (match(board,row1,column1,bit,wordcheck,row,column,columnchange,rowchange)){
				myStack.push(StackNode(Position(row1,column1)));
				wordplaced=true;
			}
			else {		
				myStack.pop(temp);
				if (temp.pos.row==0 && temp.pos.col==0){ //if the (0,0) is getting popped which means that the string doesnt exist in the matrix.
					wordplaced=false;
					break;
				}

				row1=temp.pos.row;
				column1=temp.pos.col;
				board[row1][column1].check=true;

				if (wordcheck-1!=0){ //since the value is being popped, the letter should go back to its previous value in order to place it again.
					wordcheck--;
				}

				if (columnchange==true){ //if the column value was changed last time subtract 1 to return it to its last place.
					if (column1-1<0){
						row1--; //if column value is becoming -1 it means that its pushing the boundaries of the board. so instead row should be subtracted.
					}
					else{
						column1--;
					}
				}
				else if (rowchange==true){  //if the row value was changed last time subtract 1 to return it to its last place.
					if (row1-1<0){ //if row value is becoming -1 it means that its pushing the boundaries of the board. so instead column should be subtracted.
						column1--;
					}
					else{
						row1--; 
					}
				}
			}
					
		}
	}
	
	if (wordplaced == false){
		cout<<"The bit string "<<bit<< " could not be found.";
	}
	else{
		print(myStack,bit);
	}
}


int main(){

	int row, column;
	cout<<"Please enter the number of rows: ";
	cin>>row;
	cout<<"Please enter the number of columns: ";
	cin>>column;

	string filename;
	cout<<"Please enter the name of the input file that contains the matrix: ";
	cin>>filename;
	ifstream input;
	input.open(filename.c_str());
	//check if the file is correctly opened or not. If not ask the filename to the user again.
	while (input.fail()){
		cout<<"File cannot be opened."<<endl;
		cout<<"Please enter the name of the input file again: ";
		cin>>filename;
		input.open(filename.c_str());
	}
	dynamicstack myStack;
	cellStruct **board;
	board=new cellStruct*[row];

	for (int i=0; i<row; i++){
		board[i]=new cellStruct[column];
	}

	int rowplace=0;
	int columnplace=0;
	char number;
	
	while (input.get(number)){ // this part puts the input into the board and fills it.
		if (number!='1' && number!='0'){
			columnplace=0;
			rowplace++;
		}
		else if (rowplace<row && columnplace<column){
			board[rowplace][columnplace].num=number;
			board[rowplace][columnplace].check=false;
			columnplace++;
		}
		else{
			columnplace=0;
			rowplace++;
		}
	}
	
	string bit;
	cout<<"Please enter a string of bits to search (CTRL+Z to quit): ";
	while (cin>>bit){
		solve(board,row,column,myStack,bit);
		cout<<endl;
		cout<<"Please enter a string of bits to search (CTRL+Z to quit): ";
	}

	//Code taken from NQueen.cpp
	 StackNode tmp;
    while (!myStack.isEmpty()) //end of the program, prevent memory leaks
    {
        myStack.pop(tmp);
    }

    for (int i = 0; i < row; i++)
    {
        delete[] board[i];
    }
    delete[] board;
	//Code taken from NQueen.cpp

	cout<<endl;
	cout<<"Program ended successfully!"<<endl;
	return 0;
}