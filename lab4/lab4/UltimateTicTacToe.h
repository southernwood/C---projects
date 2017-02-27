#ifndef ULTIMATETICTACTOEGAME_H
#define ULTIMATETICTACTOEGAME_H
#include <iostream>
#include"GameBase.h"
#include"TicTacToeGame.h"
#include<string>
#include<vector>

class UltimateTicTacToeGame :public GameBase {
	friend ostream &operator<<(ostream &out, const UltimateTicTacToeGame &game);
public:
	UltimateTicTacToeGame();

private:
	bool subdone(unsigned int index);
	unsigned  int suggest_for_X();
	unsigned  int suggest_for_O();
	
	bool done();
	bool draw();
	virtual int play();

	int turn();
	void print();
	vector<TicTacToeGame> tic;
	unsigned int confine;
	unsigned int last_board;
};


#endif