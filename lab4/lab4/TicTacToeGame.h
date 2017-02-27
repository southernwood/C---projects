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
	friend class UltimateTicTacToeGame;
public:
	TicTacToeGame();
	TicTacToeGame(int n);
	TicTacToeGame(const TicTacToeGame &game); //overload the default copy method


private:
	bool subdone(unsigned int index);
	unsigned  int suggest_for_X();
	unsigned  int suggest_for_O();
	int subborad;
	
	bool done();
	bool draw();
	
	int turn();
	void print();

};


#endif
