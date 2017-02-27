#ifndef GameBase_H
#define GameBase_H
#include"ErrorCode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "gamePiece.h"

using namespace std;
class GameBase
{
	friend ostream &operator<<(ostream &out, const GameBase &game);

public:
	GameBase();
	~GameBase();
	
    int play();
	bool auto_play;
	static GameBase* selectgame(int c,char* v[]);
protected:
	unsigned int broadDimension_x;
	unsigned int broadDimension_y;
	vector<gamePiece> gamePiece_;
	unsigned int number_of_blanks;
	string player_x;
	string player_o;
	set<int> pointLeft_;
	bool turnx;
	bool pro_winx;
	bool pro_wino;
	int maxlength;
	int number_connect_;
	int prompt(unsigned &x, unsigned&y);
	virtual int turn()=0;
	virtual bool done()=0;
	virtual bool draw()=0;
	virtual void print()=0;
	virtual bool subdone(unsigned int index)=0;

    virtual unsigned  int suggest_for_X()=0;
	virtual unsigned  int suggest_for_O()=0;
};

ostream & operator<<(ostream &out, const GameBase &game);
#endif