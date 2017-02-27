// lab1.cpp 
//author: weiqing wang wang.weiqing@wustl.edu

//purpose : open a file and read strings and numbers form it, then print them seperately

#include "stdafx.h"
#include "lab1.h"
#include "game_piece.h"
#include "game_board.h"
#include<iostream>
#include<vector>
#include <string>
#include <sstream>
#include <fstream>
#include<ctype.h>

using namespace std;

int readFile(vector<string> &str, char * program_name) {
	string buffer;
	ifstream ifs(program_name);
	if (ifs.is_open()) {
		while (ifs >> buffer) {
			str.push_back(buffer);

		}



		ifs.close();
		return funReturn::success;
	}
	else {
		std::cout<< "can't open the file." << endl;
		return funReturn::file_open_failed;

	}



}

int usage(char *program_name,string str) {
	std::cout << "usage: " << program_name <<" "<<str<< endl;
	return funReturn::command_line_wrong;


}

void transChar(string &str){

	for (unsigned i = 0; i < str.length(); ++i){

		
		if (str.at(i) >= 'A' && str.at(i) <= 'Z'){
			str.at(i) += ('a'-'A');
			
		}

	}

	return;


}


int print_game_piece(const vector<game_piece> &game_piece1, unsigned board_dimension_x, unsigned board_dimension_y){

	int index;
	for (unsigned x = 0; x < board_dimension_x; ++x){
		for (unsigned y = 0; y < board_dimension_y; ++y){

			index = y*board_dimension_x + x;
			if (index < game_piece1.size()){
				cout << "(" << x << ", " << y << ") " << game_piece1[index].piece_displaced << endl;
			}

			else{
				return funReturn::size_vertor_not_match;
			}
		}
	}




}

int main(int argc, char* argv[])
{

	if (argc != arrayIndex::commandNumber) {

		return usage(argv[arrayIndex::functionName],"<input_file_name>");


	}

	ifstream ifs(argv[arrayIndex::inputFileName]);
	if (!ifs.open){

		return funReturn::file_open_failed;


	}
	int message;
	unsigned horizontal_extent, vertical_extent;
	message = read_dimension(ifs, horizontal_extent, vertical_extent);
	 
	while (message == funReturn::cannot_extract_dimension){
		message = read_dimension(ifs, horizontal_extent, vertical_extent);
	}

	if (message != funReturn::success){
		return message;
	}


	int size = horizontal_extent*vertical_extent;
	vector<game_piece> game_pieceArray;

	for (int i = 0; i < size; ++i){
		game_piece game_piece;
		game_piece.piece_color = piece_color::noColor;
		game_piece.piece_displaced = " ";
		game_pieceArray.push_back(game_piece);

	}
	

	message=read_game_piece(ifs, game_pieceArray, horizontal_extent, vertical_extent);

	if (message != 0){
		cout << "can't not find well defined game piece." << endl;
		return message;
	}

	return funReturn::success;
}
