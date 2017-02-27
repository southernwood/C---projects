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
#include <memory>

using namespace std;
class GameBase
{
	friend ostream &operator<<(ostream &out, const GameBase &game);


public:

    virtual int play();
	static shared_ptr<GameBase> instance();
	bool auto_play;
	static void selectgame(int c,char* v[]);
	vector<gamePiece> gamePiece_;   // make it public for the easy access fo
protected:
	unsigned int broadDimension_x;
	unsigned int broadDimension_y;
	
	unsigned int number_of_blanks;
	string player_x;
	string player_o;
	set<int> pointLeft_;
	bool turnx;
	bool pro_winx;
	bool pro_wino;
	int maxlength;
	unsigned int number_connect_;
	string gameName_;
	virtual int prompt(unsigned &x, unsigned&y);
	virtual int readGame(string gameName);
	virtual int saveGame(string gameName,bool save);
	virtual int saveDoneGame(string gameName);

	virtual int read_dimension(ifstream &ifs, unsigned int &dimension1, unsigned int &dimension2);
	virtual int read_game_piece(ifstream &ifs);
	//int read_game_info(ifstream &ifs);

	string Color_intToString(int i);
	int Color_stringToInt(string str);
	
	static shared_ptr<GameBase> smartPoint;
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