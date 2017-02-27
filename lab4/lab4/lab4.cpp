//weiqing wang;yu he;lab4
//e-mail:wang.weiqing@wustl.edu heyu@wustk.edu


#include "stdafx.h"
#include"ErrorCode.h"
//#include"gamePiece.h"
//#include"TicTacToeGame.h"
//#include "Gumoku.h"
#include "GameBase.h"
#include"sudoku.h"
#include "usage3.h"

#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
	try {
		shared_ptr<GameBase> game;
		game->selectgame(argc, &argv[0]);
		game = game->instance();
		int returnvalue = game->play();

		return returnvalue;

	}

	catch (enum funReturn &n) {
		if (n == funReturn::command_line_wrong) {
			usage(argv[0]);
		}
		else if (n == funReturn::bad_alloc) {
			cout << "can't allocate the memory" << endl;
			return  funReturn::bad_alloc;
		}
	}

	//Sudoku game;
	//game.play();
	//return 0;
	

}
