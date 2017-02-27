//lab1.h
//author: weiqing wang wang.weiqing@wustl.edu

//purpose : open a file and read strings and numbers form it, then print them seperately



#ifndef LAB1_H_
#define LAB1_H_


#include "stdafx.h"
#include<vector>
#include <string>


using namespace std;

int usage(char *program_name);
int readFile(vector<string> &str, char * program_name);
int print_game_piece(const vector<game_piece> &game_piece1, unsigned board_dimension_x, unsigned board_dimension_y);

enum funReturn{ 

	success = 0,
	file_open_failed = 1,
	//no_file_name_given = 2,
	command_line_wrong,
	cannot_read_line = 3,
	cannot_extract_dimension = 4,
	cannot_extract_game_piece_info = 5,
	fail_find_wellDefinitioned_piece = 6,
	size_vertor_not_match = 7,


};

enum arrayIndex{

	functionName = 0,
	inputFileName = 1,
	commandNumber = 2


};






#endif