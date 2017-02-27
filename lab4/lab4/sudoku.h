#ifndef SUDOKU_H
#define SUDOKU_H
#include"GameBase.h"
#include"gamePiece.h"
#include <iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;//
class Sudoku:public GameBase{
	friend ostream &operator<<(ostream &out, const Sudoku &game);
public:
	int play();
public:
	Sudoku();
	~Sudoku();
private:

	bool done();
	bool draw();
	bool subdone(unsigned int index);
	int readGame(string gameName);
	int saveGame(string gameName, bool save);
	int turn();
	void print();
	//new member
	unsigned int number_of_played;

	unsigned  int suggest_for_X();
	unsigned  int suggest_for_O();
	int prompt(unsigned &x, unsigned&y,unsigned&n);

};




#endif