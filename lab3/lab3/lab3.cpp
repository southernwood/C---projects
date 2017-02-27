#include "stdafx.h"
#include"ErrorCode.h"
#include"gamePiece.h"
#include"TicTacToeGame.h"
#include "Gumoku.h"
#include "GameBase.h"
#include "usage3.h"

#include<iostream>

using namespace std;
//
//int usage(char *program_name, string str) {
//	cout << "usage: " << program_name << " " << str << endl;
//	cout << "or "<< program_name << " " << str << " "<<"auto_player"<<endl;
//	return funReturn::command_line_wrong;
//}

int main(int argc, char *argv[])
{




	try {
		GameBase* game = GameBase::selectgame(argc, &argv[0]);

		int returnvalue = game->play();
		delete game;
		return returnvalue;

	}

	catch (enum funReturn &n) {
		//cout << "n= " << n << endl;
		if (n == funReturn::command_line_wrong) {
			usage(argv[0]);
		}

		else if (n == funReturn::bad_alloc) {
			cout << "can't allocate the memory" << endl;
			return  funReturn::bad_alloc;
		}
	}


	//return 0;



}


