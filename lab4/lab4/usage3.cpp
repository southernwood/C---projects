#include "stdafx.h"
#include "usage3.h"
#include <string>
#include <iostream>
#include"ErrorCode.h"
using namespace std;

int usage(char * program_name) {

	cout << "usage: please input:"<<program_name<<"  and game name:  TicTacToe (or Gumoku)"<< endl
		<< "Purpose:play game 3*3 TicTacTeo(or 19*19 Gumoku)"
		<< endl;

	return 0;
}