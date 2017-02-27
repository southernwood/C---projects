#ifndef GAMEPIECE_H_
#define GAMEPIECE_H_
#include <iostream>


using namespace std;

enum piece_color{
	noColor = 0,
	red = 1,
	black = 2,
	white = 3,
	blue = 4,
	wrongColor = 99,
};

struct gamePiece
{
	int piece_color;
	gamePiece();
	string piece_name;
	string piece_displaced;
	int x_;
	int y_;
	int adj[8];
};

void computerADj(int *adj, int x, int y, int horizental, int vertical);


#endif