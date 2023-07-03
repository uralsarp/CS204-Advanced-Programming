#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include "uralsarp_Sipahi_UralSarp_hw6_board.h"
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

template <class itemType>
class Player{

	private:
		int score;
		Board<itemType> &board;

	public:
		Player::Player(Board<itemType> &board) //player constructor
		: board(board), score(0)
		{}

		itemType openCard(int r, int c); //open the card with the given indexes
		bool validMove(int r, int c); // check if the move is valid or not
		void increaseNumberOfSuccess(); //increase the score of the player
		int getNumberOfSuccess(); //get the score of the player
};

#include "uralsarp_Sipahi_UralSarp_hw6_player.cpp"
#endif









