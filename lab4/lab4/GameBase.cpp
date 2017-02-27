
#include"stdafx.h"
#include"TicTacToeGame.h"
#include "Gumoku.h"
#include"sudoku.h"
#include "ErrorCode.h"
#include"gamePiece.h"
#include "GameBase.h"
#include"UltimateTicTacToe.h"

#include<iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include<time.h>


using namespace std;

shared_ptr<GameBase> GameBase::smartPoint = nullptr;

int GameBase::prompt(unsigned &x, unsigned&y){
	while (true){
		cout << "Please enter 2 coordinates (or quit) :";
		x = 0; y = 0;
		string str;
		if (!getline(cin, str)){
			cout << "Plese enter a valid coordinates: x,y or x.y or x y (within (1, "<<broadDimension_x<<") )"<<endl;
			cin.clear();
			continue;
		}
		if (str == "quit"){
			return funReturn::ask_to_quit;
		}
		if (str.size() < 3){
			cout << "Plese enter a valid coordinates: x,y or x.y or x y (within (1, "<<broadDimension_x<<") )"<<endl;		
			continue;
		}		
		unsigned int n = 0;
		for (; n < str.size(); ++n) {
			if (str.at(n) == ' '|| str.at(n) == '.' || str.at(n) == ',') {
				break;
			}
		}
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
			cout << "Plese enter a valid coordinates: x,y or x.y or x y (within (1, "<<broadDimension_x<<") )"<<endl;	
			continue;
		}

		if (x >0 && x < broadDimension_x+1&&y > 0 && y < broadDimension_y+1) {
			x=x-1;
			y=y-1;
			return funReturn::success;
		}
		else {
			cout << "Plese enter a valid coordinates: x,y or x.y or x y (within (1, "<<broadDimension_x<<") )"<<endl;	
		}

	}
}

int GameBase::play(){

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
			saveDoneGame(gameName_);
			return funReturn::game_draw;
		}

		if (done()){
			if (turnx){
				cout << "Congratulation!!! Player 2 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
				return saveDoneGame(gameName_);
			}
			else{
				cout << "Congratulation!!! Player 1 wins!!!!" << endl;
				cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
				return saveDoneGame(gameName_);
			}
			return funReturn::success;
		}

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
		
		if (draw()){
			cout << "no winning moves remain!!!" << endl;
			cout << broadDimension_x*broadDimension_y - number_of_blanks << " turns were played." << endl;
			saveDoneGame(gameName_);
			return funReturn::game_draw;

		}

	}

}

ostream & operator<<(ostream &out, const GameBase &game){

	for (int y = game.broadDimension_y-1; y >= 0; --y){
			out << setw(game.maxlength)<<y+1;
			for (unsigned int x = 0; x < game.broadDimension_x; ++x){
				unsigned int index = game.broadDimension_x*y + x;
				out <<game.gamePiece_[index].piece_displaced<<setw(game.maxlength);
			}
			out << endl;
		}
		out << " ";
		for (unsigned x = 0; x < game.broadDimension_x; ++x){
			out << x+1<<setw(game.maxlength);
		}
		return out;

}

void GameBase::selectgame(int c,char* v[]){
	if (smartPoint != nullptr) {
		throw funReturn::alreay_has_game;

	}
	else {
		if (c != arrayIndex::commandNumber&&c != arrayIndex::selectcommandNumber) {
			throw funReturn::command_line_wrong;
		}
		string str = v[arrayIndex::gameName];
		if (str == "TicTacToe") {
			smartPoint = make_shared<TicTacToeGame>();
			return;
		}
		if (str=="Sudoku"){
			smartPoint = make_shared<Sudoku>();
		//	cout<<"chosing the soduku"<<endl;
		return;
		}
		if (str == "UltimateTicTacToe") {
			smartPoint = make_shared<UltimateTicTacToeGame>();
			return;
		}
		if (c == selectcommandNumber&&str == "Gomoku") {
			istringstream temp(v[2]);
			istringstream temp2(v[3]);
			int size, number_connect;
			if (temp >> size&&temp2 >> number_connect) {
				if (size >= number_connect) {

					smartPoint = make_shared<Gumoku>(size, number_connect);
					return;
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
		if (str == "Gomoku") {
			smartPoint = make_shared<Gumoku>();

			return;
		}
		throw funReturn::command_line_wrong;
	}


	
}

shared_ptr<GameBase> GameBase::instance() {
	if (smartPoint != nullptr) {
		return smartPoint;
	}
	else {
		throw funReturn::bad_alloc;
	}
}

string GameBase::Color_intToString(int i) {
	{

	string str = "default";

	switch (i)
	{
	case piece_color::noColor:
		str = "nocolor";
		break;
	case piece_color::red:
		str = "red";
		break;
	case piece_color::black:
		str = "black";
		break;
	case piece_color::white:
		str = "white";
		break;
	case piece_color::blue:
		str = "blue";
		break;
	case piece_color::wrongColor:
		str = "wrongcolor";
		break;
	default:
		str = "wrongcolor";
		break;

	}
	return str;
}
}

int GameBase::Color_stringToInt(string str) {

	if (str == "red") {
		return piece_color::red;
	}
	else if (str == "black")
	{
		return piece_color::black;
	}
	else if (str == "white") {
		return piece_color::white;
	}
	else if (str == "blue") {
		return piece_color::blue;
	}
	else {
		for (unsigned i = 0; i < str.length(); ++i) {

			if (str.at(i) >= '!')
				return piece_color::wrongColor;
		}
		return piece_color::noColor;
	}
}

int  GameBase::read_dimension(ifstream& ifs, unsigned int& dimension1, unsigned int &dimension2) {

	string line_1;
	if (!getline(ifs, line_1)) {
		return funReturn::cannot_read_line;
	}
	istringstream iss(line_1);
	if (iss >> dimension1 >> dimension2) {
		return funReturn::success;
	}
	else
	{
		return funReturn::cannot_extract_dimension;
	}
}


int GameBase::read_game_piece(ifstream &ifs) {

	string line_1;

	bool succ = false;
	while (getline(ifs, line_1)) {

		istringstream iss;
		iss.str(line_1);
		string color, name, position;
		int x, y;
		if (iss >> color >> name >> position >> x >> y) {

			int col = Color_stringToInt(color);
			int horizontal_diff = broadDimension_x - x;
			int vertical_diff = broadDimension_y - y;

			if (horizontal_diff > 0 && vertical_diff > 0) {
				int index = broadDimension_x*y + x;
				gamePiece_[index].piece_color = col;
				gamePiece_[index].piece_name = name;
				gamePiece_[index].piece_displaced = position;
				number_of_blanks--;
				pointLeft_.erase(index);
				succ = true;

			}
			else {
				continue;
			}

		}
		else {
			continue;
		}

	}

	if (succ) {
		return funReturn::success;
	}
	else {

		return funReturn::fail_find_wellDefinitioned_piece;
	}

}


int GameBase::readGame(string gameName) {
	ifstream ifs(gameName);
	if (!ifs.is_open()) {
		cout << "can't find the saved file...." << endl;
		cout << "********************start from the beginning*********************" << endl;
		cout << endl;
		return funReturn::file_open_failed;
	}
	int message;
	string line_1;
	getline(ifs, line_1);
	if (line_1 == "New game"){
		cout << "This is a new game.." << endl;
		cout << "********************start from the beginning*********************" << endl;
		cout << endl;
		ifs.close();
		return funReturn::no_data_found;
	}
	else if (line_1 == "NO DATA"){
		cout << "No data has been found...." << endl;
		cout << "*******************start from the beginning*********************" << endl;
		cout << endl;
		ifs.close();
		return funReturn::no_data_found;
	}
	else if (line_1 == "Saved Game"){

		message = read_dimension(ifs, broadDimension_x, number_connect_);


		if (message != funReturn::success) {
			ifs.close();
			return message;
		}
		//read game info


		istringstream iss;
		getline(ifs, line_1);
		player_x = line_1;
		getline(ifs, line_1);
		player_o = line_1;
		getline(ifs, line_1);
		iss.str(line_1);
		iss >> turnx >> pro_winx >> pro_wino;
		iss.clear();
		getline(ifs, line_1);
		iss.str(line_1);
		iss >> maxlength;

		broadDimension_y = broadDimension_x;
		number_of_blanks = broadDimension_x*broadDimension_y;

		for (unsigned int y = 0; y < broadDimension_y; ++y) {
			for (unsigned int x = 0; x < broadDimension_x; ++x) {
				gamePiece game1;
				game1.x_ = x;
				game1.y_ = y;
				game1.piece_displaced = " ";
				computerADj(game1.adj, x, y, broadDimension_x, broadDimension_y);
				gamePiece_.push_back(game1);

				int index = broadDimension_x*y + x;
				pointLeft_.insert(index);
			}
		}

		message = read_game_piece(ifs);

		if (message != 0) {
			cout << "can't find well defined game piece...." << endl;
			ifs.close();
			return message;
		}
	}
	else{
		cout << "can't find well defined game...." << endl;
		cout << "*******************start from the beginning*********************" << endl;
		cout << endl;
		ifs.close();
		return funReturn::no_data_found;

	}
	ifs.close();
	return success;

}

int GameBase::saveGame(string gameName, bool save){
	ofstream saveFile;
	saveFile.open(gameName);
	if (!saveFile.is_open()){
		cout << "can't opened the saved file, please check... " << gameName << endl;
		return funReturn::file_open_failed;
	}
	if (save){

		//indicate the station
		saveFile << "Saved Game" << endl;
		//save the dimension
		if (!(saveFile << broadDimension_x << " " <<number_connect_<< endl)){
			cout << "can't saved the game, please check" << endl;
			saveFile.close();
			return funReturn::can_not_save_file;
		};

		//save the members
		saveFile << player_x << endl;
		saveFile << player_o << endl;
		saveFile << turnx << " " << pro_winx << " " << pro_wino << endl;
		saveFile << maxlength << endl;


		//save the gameBroad
		for (rsize_t index = 0; index < broadDimension_x*broadDimension_y; ++index){
			if (gamePiece_[index].piece_displaced != " "){
				string color = Color_intToString(gamePiece_[index].piece_color);
				saveFile << color << " " << gamePiece_[index].piece_name << " "
					<< gamePiece_[index].piece_displaced << " " << gamePiece_[index].x_ << " " << gamePiece_[index].y_ << endl;
			}
		}
		
		cout << "save file successfully" << endl;
		
	}
	else{
		saveFile << "NO DATA" << endl;

	}
	saveFile.close();
	return funReturn::success;

}
int GameBase::saveDoneGame(string gameName){
	ofstream saveFile;
	saveFile.open(gameName);
	if (!saveFile.is_open()){
		cout << "cann't opened the saved file, please check... " << gameName << endl;
		return funReturn::file_open_failed;
	}
	saveFile << "New game" << endl;
	saveFile.close();
	return success;

}