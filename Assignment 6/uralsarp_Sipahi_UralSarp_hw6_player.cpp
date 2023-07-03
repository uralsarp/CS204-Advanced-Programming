
#include "uralsarp_Sipahi_UralSarp_hw6_player.h"
#include "uralsarp_Sipahi_UralSarp_hw6_board.h"

using namespace std;


template <class itemType>
itemType Player<itemType>::openCard(int rowindex, int columnindex){
	board.open(rowindex,columnindex); //open the card
	return board.getValue(rowindex,columnindex); //return the value of the corresponding indexes
}

template <class itemType>
bool Player<itemType>::validMove(int rowindex, int columnindex){ 
	int columncheck=board.getColumn(); //column value of the original board
	int rowcheck=board.getRow(); //row value of the original board
	if ((columnindex<columncheck) && (rowindex<rowcheck)){ //if the indexes are out of the range of the board or not
		if (board.getClosed(rowindex,columnindex)==false){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

template <class itemType>
void Player<itemType>::increaseNumberOfSuccess(){ 
	score++;
}

template <class itemType>
int Player<itemType>::getNumberOfSuccess(){
	return score;
}
