//lab1.h
//author: weiqing wang wang.weiqing@wustl.edu

//purpose : open a file and read strings and numbers form it, then print them seperately



#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include "stdafx.h"
#include "game_piece.h"
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
#include"lab1.h"
using namespace std;



int read_dimension(ifstream &ifs, unsigned &dimension1, unsigned &dimension2);

int read_game_piece(ifstream &ifs, vector<game_piece> &game_piece1, unsigned &horizontal_dimension, unsigned &vertical_dimension);









#endif