#ifndef GUMOKU_H
#define GUMOKU_H
#include"GameBase.h"
#include"gamePiece.h"

#include <iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

class Gumoku:public GameBase{
	
public:
	Gumoku();
	~Gumoku();
	Gumoku(int size, int number_connect);

private:
	
	bool subdone(unsigned int index);
	unsigned  int suggest_for_X();
	unsigned  int suggest_for_O();
	
	bool done();
	bool draw();
	
	int turn();

	void print();

};


#endif
