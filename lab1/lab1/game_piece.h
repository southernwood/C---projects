//lab1.h
//author: weiqing wang wang.weiqing@wustl.edu

#ifndef GAME_H_
#define GAME_H_

#include "stdafx.h"
#include <string>
#include<iostream>
using namespace std;


enum piece_color{

	noColor = 0,
	red = 1,
	black = 2,

	white = 3,


	wrongColor = 99




};



string Color_intToString(int i);

enum piece_color Color_stringToInt(string str);


struct game_piece
{
	int piece_color;
	string piece_name;
	string piece_displaced;

};




#endif