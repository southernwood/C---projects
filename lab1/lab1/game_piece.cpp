//lab1.h
//author: weiqing wang wang.weiqing@wustl.edu

#include "stdafx.h"
#include "game_piece.h"
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
#include"lab1.h"
using namespace std;



string Color_intToString(int i){


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
	case piece_color::wrongColor:
		str = "wrongcolor";
		break;
	default:
		str = "wrongcolor";
		break;
			
	}

	
	return str;

}

enum piece_color Color_stringToInt(string str){

	if (str == "red"){
		return piece_color::red;
	}
	else if (str == "black")
	{
		return piece_color::black;
	}
	else if (str == "white"){
		return piece_color::white;
	}
	else{
		for (unsigned i = 0; i < str.length(); ++i){

			if (str.at(i) >= '!')
				return piece_color::wrongColor;
		}


		return piece_color::noColor;
	}
}

