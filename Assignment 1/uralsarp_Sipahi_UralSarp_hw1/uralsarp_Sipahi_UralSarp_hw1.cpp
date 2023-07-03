#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

//Ural Sarp Sipahi 28093


void printMatrix(const vector<vector<char>> & mat){
	for (int j = 0; j < mat.size(); j++){
		for (int k = 0; k < mat[0].size(); k++){
			cout << setw(4) << mat[j][k];
		}
		cout << endl;
	}
}
int spaceTabCounter(string line){ //function to calculate all the tab and space characters inside a string
	int count=0;
	for (int i=0; i<line.size();i++){
		if ((line[i]==' ')||(line[i]=='\t')){
			count++;
		}
	}
	return count;
}
void matrixOp(vector<vector<char>> & matrix, string word, int x, int y, string direction, string orient,int row, int column){ //function to replace the word into the matrix
	char letter;
	int newy=y;
	int newx=x;
	bool stop=true; //boolean value to check if the first letter can be placed in the matrix or not
	bool wordplaced=true; //boolean value to check if the word is succesfully placed or not
	vector<vector<char>> temp; //temporary matrix to store the letters first. If all the words are not placed into this temp matrix, it is discarded. Else the main matrix is equalized to the temp matrix.
	temp=matrix;
	letter=word.at(0);
	if (temp[x][y] == '-'){
		temp[x][y]=letter;
	}
	else{
		cout<<"\""<<word<<"\""<<" could not be put into the matrix with given starting point: "<<x<<","<<y<<" "<<"direction: "<<direction<<" "<<"orientation: "<<orient<<endl;
		stop=false;
		printMatrix(matrix);
	}
	if (stop==true){
		for (int i=1; i<word.length();i++){
			letter=word.at(i);
			if (direction=="r"){
				if (((newy+1)<column) && (temp[newx][newy+1] == '-')){
					temp[newx][newy+1] = letter;
					newy++; //update y value in order for the next letter to try right first.
				}
				else {
					if (orient=="CW"){
						if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down first (if right is not available)
							temp[newx+1][newy] = letter;
							newx++;
						}
						else{
							if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left
								temp[newx][newy-1] = letter;
								newy--;
							}
							else {
								if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up
									temp[newx-1][newy] = letter;
									newx--;
								}
								else {
									wordplaced=false;
								}
							}
						}
					}
					else if (orient=="CCW"){
						if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up first (if right is not available)
							temp[newx-1][newy] = letter;
							newx--;
						}
						else{
							if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left
								temp[newx][newy-1] = letter;
								newy--;
							}
							else {
								if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down
									temp[newx+1][newy] = letter;
									newx++;
								}
								else{
									wordplaced=false;
								}
							}
						}
					}
				}
			}
			else if (direction=="l"){
				if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){
					temp[newx][newy-1] = letter;
					newy--; //update y value in order for the next letter to try left first.
				}
				else{
					if (orient=="CW"){
						if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up first (left was not available)
							temp[newx-1][newy] = letter;
							newx--;
						}
						else{
							if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right
								temp[newx][newy+1] = letter;
								newy++;
							}
							else{
								if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down
									temp[newx+1][newy] = letter;
									newx++;
								}
								else{
									wordplaced=false;
								}
							}
						}
					}
					else if (orient=="CCW"){
						if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down first (left was not available)
							temp[newx+1][newy] = letter;
							newx++;
						}
						else{
							if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right
								temp[newx][newy+1] = letter;
								newy++;
							}
							else{
								if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up
									temp[newx-1][newy] = letter;
									newx--;
								}
								else{
									wordplaced=false;
								}
							}
						}
					}
				}
			}
			else if (direction=="u"){
				if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){
					temp[newx-1][newy] = letter;
					newx--; //update x value in order for the next letter to try up first.
				}
				else {
					if (orient=="CW"){
						if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right first (if right is not available)
							temp[newx][newy+1] = letter;
							newy++;
						}
						else{
							if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down
								temp[newx+1][newy] = letter;
								newx++; 
							}
							else {
								if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left
									temp[newx][newy-1] = letter;
									newy--;
								}
								else {
									wordplaced=false;
								}
							}
						}
					}
					else if (orient=="CCW"){
						if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left first (if right is not available)
							temp[newx][newy-1] = letter;
							newy--;
						}
						else{
							if (((newx+1)<row) && (temp[newx+1][newy] == '-')){ //try down
								temp[newx+1][newy] = letter;
								newx++; 
							}
							else {
								if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right
									temp[newx][newy+1] = letter;
									newy++;
								}
								else{
									wordplaced=false;
								}
							}
						}
					}
				}
			}
			else if (direction=="d"){
				if (((newx+1)<row) && (temp[newx+1][newy] == '-')){
					temp[newx+1][newy] = letter;
					newx++; //update x value in order for the next letter to try down first.
				}
				else {
					if (orient=="CW"){
						if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left first (if right is not available)
							temp[newx][newy-1] = letter;
							newy--;
						}
						else{
							if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up
								temp[newx-1][newy] = letter;
								newx--;
							}
							else {
								if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right
									temp[newx][newy+1] = letter;
									newy++;
								}
								else {
									wordplaced=false;
								}
							}
						}
					}
					else if (orient=="CCW"){
						if (((newy+1)<column) && (temp[newx][newy+1] == '-')){ //try right first (if right is not available)
							temp[newx][newy+1] = letter;
							newy++;
						}
						else{
							if (((newx-1)>=0) && (temp[newx-1][newy] == '-')){ //try up
								temp[newx-1][newy] = letter;
								newx--;
							}
							else {
								if (((newy-1)>=0) && (temp[newx][newy-1] == '-')){ //try left
									temp[newx+1][newy] = letter;
									newx++;
								}
								else{
									wordplaced=false;
								}
							}
						}
					}
				}
			}
		}
		if (wordplaced==true){
			matrix=temp;
			cout<<"\""<<word<<"\""<<" was put into the matrix with given starting point: "<<x<<","<<y<<" "<<"direction: "<<direction<<" "<<"orientation: "<<orient<<endl;
			printMatrix(matrix);
		}
		else if (wordplaced==false){
			cout<<"\""<<word<<"\""<<" could not be put into the matrix with given starting point: "<<x<<","<<y<<" "<<"direction: "<<direction<<" "<<"orientation: "<<orient<<endl;
			printMatrix(matrix);
		}
	}
}	


int main(){


	string filename;
	cout<<"Please enter the name of the file: ";
	cin>>filename;
	ifstream input;
	input.open(filename.c_str());
	//check if the file is correctly opened or not. If not ask the filename to the user again.
	while (input.fail()){
		cout<<"File name is incorrect, please enter again: ";
		cin>>filename;
		input.open(filename.c_str());
	}
	//get the first line of the file and assign the row and column values.
	string line;
	int row, column;
	getline(input,line);
	istringstream strstream(line);
	strstream>>row>>column;

	//check if row and column values are >=0.
	if ((row < 0) || (column < 0)){
		cout<<"Invalid number for row and/or column!"<<endl;
	}

	else{
		vector<vector<char>> matrix; //empty matrix with no rows and columns
		for (int j = 0; j < row; j++){
			vector<char> temp;  //creating an empty temporary vector
			for (int k = 0; k < column; k++){
				temp.push_back('-');  //adding dash character to all the unassigned values
			}
			matrix.push_back(temp);  
		}
		int tempx,tempy; 
		int x,y; //the values that are needed to place the first letter of the given word in the file to the matrix
		string tempdirection,temporient;
		string word,direction,orient;
		while (getline(input,line)){
			istringstream strstream(line);
			strstream>>word>>tempx>>tempy>>tempdirection>>temporient;
			if ((row <= tempx) || (column <= tempy) || (tempx < 0) || (tempy < 0)){
				cout<<"Starting point is out of range! Point: "<<tempx<<","<<tempy<<endl;
			}
			else{
				x=tempx;
				y=tempy;
				if ((tempdirection != "r") && (tempdirection != "l") && (tempdirection != "u") && (tempdirection != "d")){
					cout<<"Invalid input for direction! Direction: "<<tempdirection<<endl;
				}
				else{
					direction=tempdirection;
					if ((temporient != "CW") && (temporient != "CCW")){
						cout<<"Invalid input for orientation! Orientation: "<<temporient<<endl;
					}
					else{
						orient=temporient;
						int spaceTab;
						spaceTab=spaceTabCounter(line); //number of tab and space characters in a line.
						if ((((word.length())+(orient.size())+3)!=(line.length()-spaceTab))){ 
							cout<<"Invalid line! Number of values is different than 5."<<endl;
						}
						else{ 
							matrixOp(matrix,word,x,y,direction,orient,row,column); //Vector to place the letters into the matrix
						}
					}
				}
			}	
		}
	}


	return 0;
}