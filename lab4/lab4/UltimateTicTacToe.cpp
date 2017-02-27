#include"stdafx.h"
#include "TicTacToeGame.h"
#include"UltimateTicTacToe.h"
#include "ErrorCode.h"
#include<time.h>
#include<iostream>
#include <sstream>
#include <algorithm>

using namespace std;

UltimateTicTacToeGame::UltimateTicTacToeGame()
{

	for (int i = 0; i < 10; ++i) {
		TicTacToeGame game(i);
		tic.push_back(game);
	}
	broadDimension_x = broadDimension_y = 9;
	number_connect_ = 3;
	turnx = true;
	number_of_blanks = broadDimension_x*broadDimension_y;
	pro_wino = true;
	pro_winx = true;
	auto_play = false;
	player_x = "Player X: ";
	player_o = "Player O: ";
	confine = 99;
	last_board = 0;

};


bool UltimateTicTacToeGame::done() {
	return tic[9].done();

}
bool UltimateTicTacToeGame::subdone(unsigned int index) {
	
	return tic[index].done();

}


bool UltimateTicTacToeGame::draw() {

	return tic[9].draw();

}

//no longer used
unsigned int UltimateTicTacToeGame::suggest_for_X() {

	return tic[9].suggest_for_X();

}

//no longer used
unsigned int UltimateTicTacToeGame::suggest_for_O() {
	return tic[9].suggest_for_O();

}
int UltimateTicTacToeGame::play() {
	print();
	cout << endl;
	while (true) {

		int message;
		message = turn();

		if (message == funReturn::quit_the_game) {
			cout << "user quit: ";
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			return funReturn::quit_the_game;
		}
		//else if (message == funReturn::game_draw) {
		//	cout << "no winning moves remain!!!" << endl;
		//	cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
		//	return funReturn::game_draw;
		//}
		// this borad is tie
		if (tic[last_board].draw()) {
			tic[9].gamePiece_[confine].piece_displaced == "B";
			tic[9].gamePiece_[confine].piece_color = piece_color::black;
			tic[9].gamePiece_[confine].piece_name = "black_stone";
			tic[9].number_of_blanks--;
			tic[9].pointLeft_.erase(last_board);
		}
		if (tic[9].gamePiece_[last_board].piece_displaced == " " & subdone(last_board)) {
			if (turnx) {
			//	cout << tic[9] << endl;

				tic[9].gamePiece_[last_board].piece_displaced = "O";
				tic[9].gamePiece_[last_board].piece_color = piece_color::red;
				tic[9].gamePiece_[last_board].piece_name = "red_stone";
				tic[9].number_of_blanks--;
				tic[9].pointLeft_.erase(last_board);
			}
			else {
			//	cout << tic[9] << endl;

				tic[9].gamePiece_[last_board].piece_displaced = "X";
				tic[9].gamePiece_[last_board].piece_color = piece_color::blue;
				tic[9].gamePiece_[last_board].piece_name = "blue_stone";
				tic[9].number_of_blanks--;
				tic[9].pointLeft_.erase(last_board);
			}
		}
		if(tic[9].gamePiece_[confine].piece_displaced != " "){
			confine = 99;
		}

		if (done()) {
			if (turnx) {
				cout << "Congratulation!!! Player 2 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			}
			else {
				cout << "Congratulation!!! Player 1 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			}
			return funReturn::success;
		}

		if (turnx && tic[9].number_of_blanks < 6) {
			tic[9].suggest_for_X();
			if (!tic[9].pro_winx) {
				if (tic[9].number_of_blanks>1) {
					tic[9].suggest_for_O();
				}
				else {
					tic[9].pro_wino = false;
				}
			}
		}
		else if(tic[9].number_of_blanks < 6){
			tic[9].suggest_for_O();
			if (!tic[9].pro_wino) {
				if (tic[9].number_of_blanks > 1) {
					tic[9].suggest_for_X();
				}
				else {
					tic[9].pro_winx = false;
				}
			}
		}

		if (draw()) {
			cout << "no winning moves remain!!!" << endl;
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			return funReturn::game_draw;

		}

	}


}

int UltimateTicTacToeGame::turn() {
	
	if (turnx) {

		cout << "Player X's turn:" << endl;

		int sub_sign;
		unsigned int x;
		unsigned int y;
		while (true) {
			int message = prompt(x, y);
			if (message == funReturn::ask_to_quit) {

				cout << "using quit..." << endl;

				return funReturn::quit_the_game;
			}

			if (x <= 2 && y <= 2) {
				sub_sign = 0;

			}
			else if (x > 2 && x <= 5 && y <= 2) {
				sub_sign = 1;
			}
			else if (x > 5 && y <= 2) {
				sub_sign = 2;
			}
			else if (x <= 2 && y > 2 && y <= 5) {
				sub_sign = 3;

			}
			else if (x > 2 && x <= 5 && y > 2 && y <= 5) {
				sub_sign = 4;
			}
			else if (x > 5 && y > 2 && y <= 5) {
				sub_sign = 5;
			}
			else if (x <= 2 && y > 5) {
				sub_sign = 6;
			}
			else if (x > 2 && x <= 5 && y > 5) {
				sub_sign = 7;
			}
			else if (x > 5 && y > 5) {
				sub_sign = 8;
			}
			unsigned int sub_x = x % 3;
			unsigned int sub_y = y % 3;
			unsigned int sub_index = 3 * sub_y + sub_x;

			if (tic[sub_sign].gamePiece_[sub_index].piece_displaced == " " && (confine == sub_sign || confine == 99)) {
				tic[sub_sign].gamePiece_[sub_index].piece_displaced = "X";
				tic[sub_sign].gamePiece_[sub_index].piece_color = piece_color::blue;
				tic[sub_sign].gamePiece_[sub_index].piece_name = "blue_stone";
				tic[sub_sign].number_of_blanks--;
				tic[sub_sign].pointLeft_.erase(sub_index);
				cout << *this << endl;
				cout << endl;
				//	cout << "sub sign is: " << sub_sign<<endl;
				
				player_x = player_x + to_string(x + 1) + ", " + to_string(y + 1) + "; ";
				cout << player_x << endl;
				cout << "-------------------------" << endl;
				last_board = sub_sign;
				confine = sub_index;
				--number_of_blanks;
				turnx = false;
				return funReturn::success;
			}
			else {
				// place at the wrong board
				if (confine != sub_sign) {
					cout << "You must place at the No."<<confine+1<<" broad, please check with the rules " << endl;
				}
				else {
					cout << "("<<x << ", " << y << ") has already been taken! Plese enter a valid coordinates!" << endl;
				}
			}
		}
	}
	else {


		cout << "Player O's turn:" << endl;
		int sub_sign;
		unsigned int x;
		unsigned int y;
		while (true) {
			int message = prompt(x, y);
			if (message == funReturn::ask_to_quit) {

				cout << "using quit..." << endl;

				return funReturn::quit_the_game;
			}

			if (x <= 2 && y <= 2) {
				sub_sign = 0;

			}
			else if (x > 2 && x <= 5 && y <= 2) {
				sub_sign = 1;
			}
			else if (x > 5 && y <= 2) {
				sub_sign = 2;
			}
			else if (x <= 2 && y > 2 && y <= 5) {
				sub_sign = 3;

			}
			else if (x > 2 && x <= 5 && y > 2 && y <= 5) {
				sub_sign = 4;
			}
			else if (x > 5 && y > 2 && y <= 5) {
				sub_sign = 5;
			}
			else if (x <= 2 && y > 5) {
				sub_sign = 6;
			}
			else if (x > 2 && x <= 5 && y > 5) {
				sub_sign = 7;
			}
			else if (x > 5 && y > 5) {
				sub_sign = 8;
			}
			unsigned int sub_x = x % 3;
			unsigned int sub_y = y % 3;
			unsigned int sub_index = 3 * sub_y + sub_x;

			if (tic[sub_sign].gamePiece_[sub_index].piece_displaced == " " && (confine == sub_sign || confine == 99)) {
				tic[sub_sign].gamePiece_[sub_index].piece_displaced = "O";
				tic[sub_sign].gamePiece_[sub_index].piece_color = piece_color::red;
				tic[sub_sign].gamePiece_[sub_index].piece_name = "red_stone";
				tic[sub_sign].number_of_blanks--;
				tic[sub_sign].pointLeft_.erase(sub_index);
				cout << *this << endl;
				cout << endl;
				//	cout << "sub sign is: " << sub_sign<<endl;
				player_o = player_o + to_string(x + 1) + ", " + to_string(y + 1) + "; ";
				cout << player_o << endl;
				cout << "-------------------------" << endl;
				last_board = sub_sign;
				confine = sub_index;
				turnx = true;
				--number_of_blanks;
				return funReturn::success;
			}
			else {
				if (confine != sub_sign) {
					cout << "You must place at the No." << confine + 1 << " broad, please check with the rules " << endl;
				}
				else {
					cout << "(" << x << ", " << y << ") has already been taken! Plese enter a valid coordinates!" << endl;
				}
			}
		}
	}
	
	return 0;
}
void UltimateTicTacToeGame::print() { cout << *this << endl; }

ostream & operator<<(ostream &out, const UltimateTicTacToeGame &game) {
	
	out << "========================" << endl;
	out << 9 << "||" << game.tic[6].gamePiece_[6].piece_displaced <<" "<< game.tic[6].gamePiece_[7].piece_displaced 
		<< " " << game.tic[6].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[7].gamePiece_[6].piece_displaced << " " <<game.tic[7].gamePiece_[7].piece_displaced 
		<< " " << game.tic[7].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[8].gamePiece_[6].piece_displaced << " " << game.tic[8].gamePiece_[7].piece_displaced 
		<< " " << game.tic[8].gamePiece_[8].piece_displaced << "||" << endl;

	out << 8 << "||" << game.tic[6].gamePiece_[3].piece_displaced << " " << game.tic[6].gamePiece_[4].piece_displaced 
		<< " " << game.tic[6].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[7].gamePiece_[3].piece_displaced << " " << game.tic[7].gamePiece_[4].piece_displaced << " " 
		<< game.tic[7].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[8].gamePiece_[3].piece_displaced << " " << game.tic[8].gamePiece_[4].piece_displaced << " " 
		<< game.tic[8].gamePiece_[5].piece_displaced << "||" << endl;

	out <<7 << "||" << game.tic[6].gamePiece_[0].piece_displaced << " " << game.tic[6].gamePiece_[1].piece_displaced 
		<< " " << game.tic[6].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[7].gamePiece_[0].piece_displaced << " " << game.tic[7].gamePiece_[1].piece_displaced << " " 
		<< game.tic[7].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[8].gamePiece_[0].piece_displaced << " " << game.tic[8].gamePiece_[1].piece_displaced << " " 
		<< game.tic[8].gamePiece_[2].piece_displaced <<"||"<< endl;

	out << "========================" << endl;

	out << 6 << "||" << game.tic[3].gamePiece_[6].piece_displaced << " " << game.tic[3].gamePiece_[7].piece_displaced << " " 
		<< game.tic[3].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[4].gamePiece_[6].piece_displaced << " " << game.tic[4].gamePiece_[7].piece_displaced << " " 
		<< game.tic[4].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[5].gamePiece_[6].piece_displaced << " " << game.tic[5].gamePiece_[7].piece_displaced << " " 
		<< game.tic[5].gamePiece_[8].piece_displaced << "||" << endl;

	out << 5 << "||" << game.tic[3].gamePiece_[3].piece_displaced << " " << game.tic[3].gamePiece_[4].piece_displaced << " "
		<< game.tic[3].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[4].gamePiece_[3].piece_displaced << " " << game.tic[4].gamePiece_[4].piece_displaced << " " 
		<< game.tic[4].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[5].gamePiece_[3].piece_displaced << " " << game.tic[5].gamePiece_[4].piece_displaced << " " 
		<< game.tic[5].gamePiece_[5].piece_displaced << "||" << endl;

	out << 4 << "||" << game.tic[3].gamePiece_[0].piece_displaced << " " << game.tic[3].gamePiece_[1].piece_displaced << " "
		<< game.tic[3].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[4].gamePiece_[0].piece_displaced << " " << game.tic[4].gamePiece_[1].piece_displaced << " " 
		<< game.tic[4].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[5].gamePiece_[0].piece_displaced << " " << game.tic[5].gamePiece_[1].piece_displaced << " " 
		<< game.tic[5].gamePiece_[2].piece_displaced << "||" << endl;
	out << "========================" << endl;

	out << 3 << "||" << game.tic[0].gamePiece_[6].piece_displaced << " " << game.tic[0].gamePiece_[7].piece_displaced << " " 
		<< game.tic[0].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[1].gamePiece_[6].piece_displaced << " " << game.tic[1].gamePiece_[7].piece_displaced << " " 
		<< game.tic[1].gamePiece_[8].piece_displaced;

	out << "||" << game.tic[2].gamePiece_[6].piece_displaced << " " << game.tic[2].gamePiece_[7].piece_displaced << " "
		<< game.tic[2].gamePiece_[8].piece_displaced << "||" << endl;

	out << 2<< "||" << game.tic[0].gamePiece_[3].piece_displaced << " " << game.tic[0].gamePiece_[4].piece_displaced << " " 
		<< game.tic[0].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[1].gamePiece_[3].piece_displaced << " " << game.tic[1].gamePiece_[4].piece_displaced << " " 
		<< game.tic[1].gamePiece_[5].piece_displaced;

	out << "||" << game.tic[2].gamePiece_[3].piece_displaced << " " << game.tic[2].gamePiece_[4].piece_displaced << " " 
		<< game.tic[2].gamePiece_[5].piece_displaced << "||" << endl;

	out << 1<< "||" << game.tic[0].gamePiece_[0].piece_displaced << " " << game.tic[0].gamePiece_[1].piece_displaced << " " 
		<< game.tic[0].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[1].gamePiece_[0].piece_displaced << " " << game.tic[1].gamePiece_[1].piece_displaced << " " 
		<< game.tic[1].gamePiece_[2].piece_displaced;

	out << "||" << game.tic[2].gamePiece_[0].piece_displaced << " " << game.tic[2].gamePiece_[1].piece_displaced << " " 
		<< game.tic[2].gamePiece_[2].piece_displaced << "||" << endl;
	out << "========================" << endl;
	out << " # 1 2 3||4 5 6||7 8 9" << endl;
	return out;

}