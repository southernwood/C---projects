//weiqing wang lab2
//wang.weiqing@wustl.edu
//inplement the tictactoe game

#include"stdafx.h"
#include"TicTacToeGame.h"
#include "Gumoku.h"
#include "ErrorCode.h"
#include"gamePiece.h"
#include<time.h>
#include "GameBase.h"
//#include "usage3.h"
#include<iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

GameBase::GameBase()
{


};
GameBase::~GameBase(){};
// check if any block fulfill the winning condition
int GameBase::prompt(unsigned &x, unsigned&y){
	while (true){
		cout << "Please enter 2 coordinates (or quit) :";

		x = 0; y = 0;
		string str;
		if (!getline(cin, str)){
			return funReturn::input_error;
		}
		if (str == "quit"){
			return funReturn::ask_to_quit;
		}
		if (str.size() < 3){
			cout << "Plese enter a valid coordinates!" << endl;
			continue;
		}
		
		unsigned int n = 0;
		for (; n < str.size(); ++n) {
			if (str.at(n) == ' '|| str.at(n) == '.' || str.at(n) == ',') {
				break;
			}

		}

		//cout << "the n is " << n << "the size is " << str.size()<<endl;
		if (n < str.size()) {
			for (unsigned int i = 0; i < n; ++i) {
				if (isdigit(str.at(i))) {
					x = x * 10 + str.at(i) - '0';
				}
				else {
					x = broadDimension_x;
					break;
				}
			}

			for (unsigned int i = n + 1; i < str.size(); ++i) {

				if (isdigit(str.at(i))) {
					y = y * 10 + str.at(i) - '0';
				}
				else {
					y = broadDimension_y;
					break;
				}
			}
		}
		else {
			cout << "Plese enter a valid coordinates!" << endl;
			continue;
		}



		if (x >= 0 && x < broadDimension_x&&y >= 0 && y < broadDimension_y) {
			return funReturn::success;
		}
		else {
			cout << "Plese enter a valid coordinates!" << endl;
		}


	}
}

int GameBase::play(){
	//cout << "here I am" << endl;
	print();
	cout << endl;
	while (true){
		
		int message;



		message = turn();

		if (message == funReturn::quit_the_game){
			cout << "user quit: ";
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			return funReturn::quit_the_game;
		}
		else if (message == funReturn::game_draw){
						cout << "no winning moves remain!!!" << endl;
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			return funReturn::game_draw;
		}

		if (done()){
			if (turnx){
				cout << "Congratulation!!! Player 2 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			}
			else{
				cout << "Congratulation!!! Player 1 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			}
			return funReturn::success;
		}

		if (number_of_blanks < broadDimension_x*broadDimension_y / 2){
			if (turnx){
				suggest_for_X();
				if (!pro_winx){
					if (number_of_blanks>1){
						suggest_for_O();
					}
					else{
						pro_wino = false;
					}
				}
			}
			else{
				suggest_for_O();
				if (!pro_wino){
					if (number_of_blanks > 1){
						suggest_for_X();
					}
					else{
						pro_winx = false;
					}
				}
			}
		}

		if (draw()){
			cout << "no winning moves remain!!!" << endl;
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			return funReturn::game_draw;

		}

	}

}

ostream & operator<<(ostream &out, const GameBase &game){

	for (int y = game.broadDimension_y-1; y >= 0; --y){
			out << setw(game.maxlength)<<y;
			for (unsigned int x = 0; x < game.broadDimension_x; ++x){
				unsigned int index = game.broadDimension_x*y + x;
				out <<setw(game.maxlength)<<game.gamePiece_[index].piece_displaced;
			}
			out << endl;
		}

		//print horizontal coordinate
		out << " ";
		for (unsigned x = 0; x < game.broadDimension_x; ++x){
			out << setw(game.maxlength)<<x;
		}
		return out;

}

GameBase* GameBase::selectgame(int c,char* v[]){
	
	if (c != arrayIndex::commandNumber&&c!=arrayIndex::selectcommandNumber) {
		//cout << "line wrong";
		throw funReturn::command_line_wrong;
		//throw 10;
	}
	string str = v[arrayIndex::gameName];
	if (str=="TicTacToe"){
		GameBase* game=new TicTacToeGame;
		if (game == 0){
			throw funReturn::bad_alloc;
		}
		return game;
	}
	if (c == selectcommandNumber&&str == "Gumoku") {
		istringstream temp(v[2]);
		istringstream temp2(v[3]);
		int size, number_connect;
		if (temp >> size&&temp2 >> number_connect) {
			if (size >= number_connect) {
				
				GameBase* game = new Gumoku(size, number_connect);

				if (game == 0) {
					throw funReturn::bad_alloc;
				}

				return game;
			}
			else {
				cout << "the game size is small than the number of connecting pieces in a row, Please check your input " << endl;
				throw funReturn::command_line_wrong;
			}
		}
		else {
			throw funReturn::command_line_wrong;
		}
		

	}
	if (str=="Gumoku"){
		GameBase* game=new Gumoku();

		if (game == 0){
			throw funReturn::bad_alloc;
		}

		return game;
	}
	throw funReturn::command_line_wrong;
	
}
