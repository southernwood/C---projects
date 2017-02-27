#include "stdafx.h"
#include "game_piece.h"
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
#include"lab1.h"
#include "game_board.h"

using namespace std;


int read_dimension(ifstream &ifs, unsigned &dimension1, unsigned &dimension2){

	string line_1;
	if (!getline(ifs, line_1)){
		return funReturn::cannot_read_line;
	}
	istringstream iss(line_1);
	if (iss >> dimension1 >> dimension2){
		return funReturn::success;
	}
	else
	{
		return funReturn::cannot_extract_dimension;
	}


}

int read_game_piece(ifstream &ifs, vector<game_piece> &game_piece1, unsigned board_horizontal_dimension, unsigned board_vertical_dimension){

	string line_1;
	istringstream iss;
	bool succ = false;
	while (getline(ifs, line_1)){

		iss.str(line_1);


		string color, name, position;
		int x, y;
		if (iss >> color >> name >> position >> x >> y){

			enum piece_color col = Color_stringToInt(color);
			int horizontal_diff = board_horizontal_dimension - x;
			int vertical_diff = board_vertical_dimension - y;
			if (horizontal_diff >= 0 && vertical_diff >= 0){
				int index = board_horizontal_dimension*y + x;
				game_piece1[index].piece_color = col;
				game_piece1[index].piece_name = name;
				game_piece1[index].piece_displaced = position;
				succ = true;

			}
			else{
				continue;
			}

		}
		else{
			continue;
		}

	}

	if (succ){
		return funReturn::success;
	}
	else{

		return funReturn::fail_find_wellDefinitioned_piece;
	}

}