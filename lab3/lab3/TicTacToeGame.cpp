//weiqing wang lab2
//wang.weiqing@wustl.edu
//inplement the tictactoe game

#include"stdafx.h"
#include"TicTacToeGame.h"
#include "ErrorCode.h"
#include"gamePiece.h"
#include<time.h>

#include<iostream>
#include <sstream>
#include <algorithm>
using namespace std;

TicTacToeGame::TicTacToeGame()
{
	broadDimension_x = 5;
	broadDimension_y = 5;
	turnx = true;
	number_of_blanks = broadDimension_x*broadDimension_y;
	player_x = "Player X: ";
	player_o = "Player O: ";
	pro_wino = true;
	pro_winx = true;
	auto_play = false;
	maxlength=1;
	for (unsigned int y = 0; y < broadDimension_y; ++y){
		for (unsigned int x = 0; x < broadDimension_x; ++x){
			gamePiece game1;
			game1.x_ = x;
			game1.y_ = y;
			computerADj(game1.adj, x, y, broadDimension_x, broadDimension_y);
			gamePiece_.push_back(game1);

			int index = broadDimension_x*y + x;
			pointLeft_.insert(index);
		}
	}


};


TicTacToeGame::~TicTacToeGame()
{
};

bool TicTacToeGame::done(){

	unsigned int size = broadDimension_x*broadDimension_y;

	for (unsigned int i = 0; i < size; ++i){
		if (subdone(i)){
			return true;
		}
	}
	return false;

}

// check if any block fulfill the winning condition
bool TicTacToeGame::subdone(unsigned int index){
	
	
	int size = broadDimension_x*broadDimension_y;
	string symbol = gamePiece_[index].piece_displaced;
	if (symbol == " "){
		return false;
	}
	
	for (int i = 0; i < 8; ++i){
		if (gamePiece_[index].adj[i] == -1){
			break;
		}

		int two = gamePiece_[index].adj[i];
		if (gamePiece_[two].piece_displaced == symbol){
			int third = two - index+two;
			
			if (third >= 0 && third < size){
				if (gamePiece_[third].piece_displaced == symbol){
					int *p;
					p = std::find(gamePiece_[two].adj, gamePiece_[two].adj + 8, third);
					if (p != gamePiece_[two].adj + 8){
						return true;
					}
				}
			}
		}

	}

	return false;

}

bool TicTacToeGame::draw(){
	

	if (done()||pro_wino||pro_winx){
		return false;
	}

	return true;
	
}


unsigned int TicTacToeGame::suggest_for_X(){


	TicTacToeGame game_virtual;
	game_virtual = *this;

	set<int>::iterator first = pointLeft_.begin();
	if (number_of_blanks <= 2){
		while (first != pointLeft_.end()){
			game_virtual.gamePiece_[*first].piece_displaced = "X";
			if (game_virtual.done()){
				return *first;
			}
			else{
				game_virtual.gamePiece_[*first].piece_displaced = " ";
				++first;
			}
		}

	}


	else{
		//for the first step
		first = pointLeft_.begin();
		while (first != pointLeft_.end()){
			game_virtual.gamePiece_[*first].piece_displaced = "X";
			if (game_virtual.done()){
				return *first;
			}
			else{
				game_virtual.gamePiece_[*first].piece_displaced = " ";
				++first;
			}
		}

		first = pointLeft_.begin();

		while (first != pointLeft_.end() && pointLeft_.size() > 0){

			game_virtual.gamePiece_[*first].piece_displaced = "X";

			game_virtual.pointLeft_.erase(*first);
			set<int>::iterator two = game_virtual.pointLeft_.begin();
				//check if O can win in the next step
			while (two != game_virtual.pointLeft_.end() && game_virtual.pointLeft_.size() > 0){
					game_virtual.gamePiece_[*two].piece_displaced = "O";
					if (game_virtual.done()){
						game_virtual.gamePiece_[*two].piece_displaced = " ";
						return *two;
					}
					else{
						game_virtual.gamePiece_[*two].piece_displaced = " ";
						++two;
					}
			}

				two = game_virtual.pointLeft_.begin();
				while (two != game_virtual.pointLeft_.end() && game_virtual.pointLeft_.size() > 0){
					game_virtual.gamePiece_[*two].piece_displaced = "X";
					if (game_virtual.done()){
						return *first;
					}
					else{
						game_virtual.gamePiece_[*two].piece_displaced = " ";
						++two;
					}

				}
		
			game_virtual.gamePiece_[*first].piece_displaced = " ";
			game_virtual.pointLeft_.insert(*first);
			++first;
			


		}
	}
	pro_winx = false;
	return funReturn::can_not_win;

}

unsigned int TicTacToeGame::suggest_for_O(){


	TicTacToeGame game_virtual;
	game_virtual = *this;

	set<int>::iterator first = pointLeft_.begin();
	if (number_of_blanks <= 2){
		while (first != pointLeft_.end()){
			game_virtual.gamePiece_[*first].piece_displaced = "O";
			if (game_virtual.done()){
				return *first;
			}
			else{
				game_virtual.gamePiece_[*first].piece_displaced = " ";
				++first;
			}
		}

	}


	else{
		//for the first step
		first = pointLeft_.begin();
		while (first != pointLeft_.end()){
			game_virtual.gamePiece_[*first].piece_displaced = "O";
			if (game_virtual.done()){
				//	pro_winx = true;
				return *first;
			}
			else{
				game_virtual.gamePiece_[*first].piece_displaced = " ";
				++first;
			}
		}

		first = pointLeft_.begin();

		while (first != pointLeft_.end() && pointLeft_.size() > 0){

			game_virtual.gamePiece_[*first].piece_displaced = "O";

			game_virtual.pointLeft_.erase(*first);
			set<int>::iterator two = game_virtual.pointLeft_.begin();
			//check if X can win in the next step
			while (two != game_virtual.pointLeft_.end() && game_virtual.pointLeft_.size() > 0){
				game_virtual.gamePiece_[*two].piece_displaced = "X";
				if (game_virtual.done()){
				
					game_virtual.gamePiece_[*two].piece_displaced = " ";
					return *two;
				}
				else{
					game_virtual.gamePiece_[*two].piece_displaced = " ";
					++two;
				}
			}

				two = game_virtual.pointLeft_.begin();
				while (two != game_virtual.pointLeft_.end() && game_virtual.pointLeft_.size() > 0){
					game_virtual.gamePiece_[*two].piece_displaced = "O";
					if (game_virtual.done()){
					return *first;
					}
					else{
						game_virtual.gamePiece_[*two].piece_displaced = " ";
						++two;
					}

				}
			
			game_virtual.gamePiece_[*first].piece_displaced = " ";
			game_virtual.pointLeft_.insert(*first);
			++first;



		}
	}
	pro_wino = false;
	return funReturn::can_not_win;

}

//int TicTacToeGame::auto_player(){
//	clock_t start;
//	start = clock();
//	while (clock() - start < 2000);//wait 2 secs
//	if (number_of_blanks > broadDimension_x*broadDimension_y - 1){
//		return *pointLeft_.begin();
//	}
//	if (turnx){
//
//		return suggest_for_X();
//	}
//	return suggest_for_O();
//
//}


int TicTacToeGame::turn(){
	if (turnx){

		cout << "Player X's turn:" << endl;

		unsigned int index;
		unsigned int x;
		unsigned int y;
		while (true){
			
			if (auto_play){
				//index = auto_player();
				if (index == funReturn::can_not_win){
					if (pointLeft_.size() > 1){
						index =* pointLeft_.begin();
					}
					else{
						return funReturn::game_draw;
					}
				}
				x = gamePiece_[index].x_;
				y = gamePiece_[index].y_;
			}
			else{

				int message = prompt(x, y);
				if (message == funReturn::ask_to_quit){
					return funReturn::quit_the_game;
				}
				index = broadDimension_x*y + x;
			}
				if (gamePiece_[index].piece_displaced == " "){

					gamePiece_[index].piece_displaced = "X";
					gamePiece_[index].piece_color = piece_color::black;
					gamePiece_[index].piece_name = "black stone";
					number_of_blanks--;
					pointLeft_.erase(index);
					cout << *this << endl;
					cout << endl;
					player_x = player_x + to_string(x) + ", " + to_string(y) + "; ";
					cout << player_x << endl;
					cout << "-------------------------" << endl;
					turnx = false;
					return funReturn::success;
				}
				else{
					cout << x << ", " << y << " has already been taken! Plese enter a valid coordinates!" << endl;
				}
			
		}

	}
	else{

		cout << "Player O's turn:" << endl;

		unsigned int index;
		unsigned int x;
		unsigned int y;
		while (true){

			if (auto_play){
				//index = auto_player();
				if (index == funReturn::can_not_win){
					if (pointLeft_.size() > 1){
						index = *pointLeft_.begin();
					}
					else{
						return funReturn::game_draw;
					}
				}
				x = gamePiece_[index].x_;
				y = gamePiece_[index].y_;
			}
			else{

				int message = prompt(x, y);
				if (message == funReturn::ask_to_quit){
					return funReturn::quit_the_game;
				}
				index = broadDimension_x*y + x;
			}
				if (gamePiece_[index].piece_displaced == " "){

					gamePiece_[index].piece_displaced = "O";
					gamePiece_[index].piece_color = piece_color::white;
					gamePiece_[index].piece_name = "white stone";
					number_of_blanks--;
					pointLeft_.erase(index);
					cout << *this << endl;
					cout << endl;
					player_o = player_o + to_string(x) + ", " + to_string(y) + "; ";
					cout << player_o << endl;
					cout << "-------------------------" << endl;
					turnx = true;
					return funReturn::success;
				}
				else{
					cout << x << ", " << y << " has already been taken! Plese enter a valid coordinates!" << endl;
				}
			
		}
	}
}

void TicTacToeGame::print(){cout<<*this<<endl;}