#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H
#include"GameBase.h"
#include"gamePiece.h"
#include <iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

class TicTacToeGame:public GameBase{
	
public:
	TicTacToeGame();
	~TicTacToeGame();


private:
	
	bool subdone(unsigned int index);
	unsigned  int suggest_for_X();
	unsigned  int suggest_for_O();
	
	bool done();
	bool draw();
	
	int turn();
	//int auto_player();
	void print();

};


#endif
