#include"stdafx.h"
#include"TicTacToeGame.h"
#include "ErrorCode.h"
#include"gamePiece.h"
#include<time.h>
#include "sudoku.h"
#include<iostream>
#include<fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

Sudoku::Sudoku(){
    broadDimension_x = 9;
	broadDimension_y = 9;
	turnx = true;
	number_of_blanks = broadDimension_x*broadDimension_y;
	number_of_played = 0;
	player_x = "Player 1: ";
	player_o = "Player 2: ";
	pro_wino = true;
	pro_winx = true;
	//auto_play = false;
	maxlength = 1;
    if (broadDimension_x > 10){
		maxlength = 2;
	}
	if (broadDimension_x > 100) {
		maxlength = 3;
	}
	readGame("sudoku0.txt");
}
Sudoku::~Sudoku(){};

int Sudoku::readGame(string gameName){
	ifstream ifs;
	ifs.open (gameName);
    if (ifs.is_open ()){
		cout<<"read from file " <<gameName<<endl;
		cout<<endl;
		cout<<"******************game start**********************"<<endl;
		cout<<endl;
	    for (unsigned int y = 0; y < broadDimension_y; ++y){
		    for (unsigned int x = 0; x < broadDimension_x; ++x){
			    gamePiece game1;
			    game1.x_ = x;
			    game1.y_ = y;
			    string s;
				ifs >> s;
				if(s=="0"){
                    game1.placedbygame=false;
					s="";
				}else{
					game1.placedbygame=true;
					--number_of_blanks;
				}
				//cout<<s<<endl;
				game1.piece_displaced=s;
				gamePiece_.push_back(game1);
			    int index = broadDimension_x*y + x;
				pointLeft_.insert(index);
				
		   }
	   } 
    }
    else{
		cout<<"can't find file sudoku0.txt, using default blank gameboard "<<endl;
		for (unsigned int y = 0; y < broadDimension_y; ++y){
		for (unsigned int x = 0; x < broadDimension_x; ++x){
			gamePiece game1;
			game1.x_ = x;
			game1.y_ = y;
			game1.placedbygame=false;
			gamePiece_.push_back(game1);
			int index = broadDimension_x*y + x;
			pointLeft_.insert(index);
		 }
	   }
   }
	//cout<<"finish read file"<<endl;
	ifs.close();
   return success;
};

int Sudoku::saveGame(string gameName,bool save){
	if(save){
		ofstream ofs(gameName); 
		if (ofs.is_open ()){
           string i; 
		   
	        for (unsigned int y = 0; y < broadDimension_y; ++y){
		       for (unsigned int x = 0; x < broadDimension_x; ++x){
			        unsigned int index = broadDimension_x*y + x;
			        string i=gamePiece_[index].piece_displaced;
					if(i==""){
					 ofs<<"0";
				}else{
					ofs<<i;
				}
			        
		       }
			   ofs<<"\n";
	        }
        
		}
		else{
			cout<<"can't open file "<<gameName<<"to save game"<<endl;
		}
	 ofs.close (); 
	}
	 return success;
};


ostream & operator<<(ostream &out, const Sudoku &game){

	for (int y = game.broadDimension_y-1; y >= 0; --y){
			
		    out << setw(game.maxlength)<<y;
			out << setw(game.maxlength)<<"||";
			for (unsigned int x = 0; x < game.broadDimension_x; ++x){
				
				unsigned int index = game.broadDimension_x*y + x;
				out<<setw(game.maxlength)<<game.gamePiece_[index].piece_displaced;
                if(x%3==2){
					out<<setw(game.maxlength)<<"||";
				}
				else{
					out<<setw(game.maxlength)<<"|";
				}
			}
			
			
			out << endl;
			if(y%3==0){
					out<<setw(game.maxlength) <<"="<<setw(game.maxlength);
				}
				else{
					out<<setw(game.maxlength)<<"-"<<setw(game.maxlength);
				}
			out << setw(game.maxlength)<<"||";
			for (unsigned int x = 0; x < game.broadDimension_x; ++x){
				
				//unsigned int index = game.broadDimension_x*y + x;
				if(y%3==0){
					out<<setw(game.maxlength) <<"="<<setw(game.maxlength);
				}
				else{
					out<<setw(game.maxlength) <<"-"<<setw(game.maxlength);
				}
                if(x%3==2){
					out<<setw(game.maxlength)<<"||";
				}
				else{
					out<<setw(game.maxlength)<<"|";
				}
			}
			out << endl;
	}
	
	out << setw(game.maxlength)<<"#";
	out << setw(game.maxlength)<<"||";
	for (unsigned int x = 0; x < game.broadDimension_x; ++x){
				out <<setw(game.maxlength)<<x;
                if(x%3==2){
					out<<setw(game.maxlength)<<"||";
				}
				else{
					out<<setw(game.maxlength)<<"|";
				}
			}
			out << endl;
		return out;

}

int Sudoku::play(){
	print();
	cout << endl;
	
	while (true) {
		int message;
		message=turn();
		
		if (message == funReturn::quit_the_game) {
			cout << "user quit: ";
			cout << number_of_played<< " moves were played." << endl;
			cout << "**********************************************" << endl;
			return funReturn::quit_the_game;
		}

		cout << number_of_played << " moves were played. There are " << number_of_blanks << " empty squares on the broad" << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		print();

		//check if player can win the game
		if (number_of_blanks == 0) {
			if (done()) {
				cout << "Congratulation!!! you have solved this sudoku!!!!" << endl;
				cout << number_of_played << " moves were played." << endl;
				return funReturn::success;

			}
		}

	}
}

// input method x,y are the coordinates and n is the value
int Sudoku::prompt(unsigned &x, unsigned&y,unsigned&n){
	while (true) {
		cout << "Please enter 2 coordinates(0-8) and 1 number(0-9) (or quit) :";
		x = 10; y = 10; n = 10;
		string str;
		if (!getline(cin, str)) {
			cout << "please enter like: 1,1,5 or 1 1 5 to place the 5 in(1,1) or 1 1 0 to erase the number in(1,1)." << endl;
			cin.clear();
			continue;
		}
		if (str == "quit") {
			return funReturn::ask_to_quit;
		}
		if (str.size() != 5) {
		//	cout << "size wrong" << endl;
			cout << "please enter like: 1,1,5 or 1 1 5 to place the 5 in(1,1) or 1 1 0 to erase the number in(1,1)." << endl;
			continue;
		}
		if ((str.at(1) == ' '&&str.at(3) == ' ') || (str.at(1) == ','&&str.at(3) == ',')|| (str.at(1) == '.'&&str.at(3) == '.')) {
			x= str.at(0) - '0';
			y = str.at(2) - '0';
			n = str.at(4) - '0';
			if (x >= 0 && x < broadDimension_x && y >= 0 && y < broadDimension_x&&n >= 0 && n <= 9) {
				//cout << "input right and x is " <<x<<" y is "<<y<<" n is "<<n<< endl;

				return funReturn::success;
			}
			cout << "please enter like: 1,1,5 or 1 1 5 to place the 5 in(1,1) or 1 1 0 to erase the number in(1,1)." << endl;

		}
		else {
			cout << "format wrong" << endl;
			cout << "please enter like: 1,1,5 or 1 1 5 to place the 5 in(1,1) or 1 1 0 to erase the number in(1,1)." << endl;
			continue;

		}

	}

}

bool Sudoku::done(){
	


	//check if the row has confliction
	for (unsigned int y = 0; y < broadDimension_y; ++y) {
		int row[10] = { -99,-1,-1,-1,-1,-1,-1,-1,-1 ,-1 };
		int n = 0;
		unsigned index;
		for (unsigned int x = 0; x < broadDimension_x; ++x) {
			index = broadDimension_x*y + x;
			n = gamePiece_[index].piece_displaced.at(0) - '0';

			// check it has confliction
			if (row[n] == -1) {
				row[n] = index;
			}
			else if (row[n] == -99) {
				cout << "(" << gamePiece_[index].x_ << "," << gamePiece_[index].y_ << ") is blank, please check your algorithm" << endl;
				return false;
			}
			else {
				int index2 = row[n];
				cout << "(" << gamePiece_[index].x_ << "," << gamePiece_[index].y_ << ") and ("
					<< gamePiece_[index2].x_ << "," << gamePiece_[index2].y_ << ") have confliction." << endl;
				cout << "please try again.." << endl;
				return false;
			}
		}
	}


	//check if the column has confliction

	for (unsigned int x = 0; x < broadDimension_x; ++x) {
		int row[10] = { -99,-1,-1,-1,-1,-1,-1,-1,-1 ,-1 };
		int n = 0;
		unsigned index;
		for (unsigned int y = 0; y < broadDimension_y; ++y) {
			index = broadDimension_x*y + x;
			n = gamePiece_[index].piece_displaced.at(0) - '0';

			// check it has confliction
			if (row[n] == -1) {
				row[n] = index;
			}
			else if (row[n] == -99) {
				cout << "(" << gamePiece_[index].x_ << "," << gamePiece_[index].y_ << ") is blank, please check your algorithm" << endl;
				return false;
			}
			else {
				int index2 = row[n];
				cout << "(" << gamePiece_[index].x_ << "," << gamePiece_[index].y_ << ") and ("
					<< gamePiece_[index2].x_ << "," << gamePiece_[index2].y_ << ") have confliction." << endl;
				cout << "please try again.." << endl;
				return false;
			}
		}
	}

	// check if subbroad has confliction

	if (subdone(0) && subdone(3) && subdone(6) && subdone(27) && subdone(30) && subdone(33) && subdone(54) && subdone(57) && subdone(60)) {
		return true;
	}

	return false;
}

//check if the row has confliction
bool Sudoku::subdone(unsigned int index) {
	
	unsigned int indexes[9];
	indexes[0] = index;
	indexes[1] = index + 1;
	indexes[2] = index + 2;
	indexes[3] = indexes[0] + 9;
	indexes[4] = indexes[1] + 9;
	indexes[5] = indexes[2] + 9;
	indexes[6] = indexes[3] + 9;
	indexes[7] = indexes[4] + 9;
	indexes[8] = indexes[5] + 9;
	int n = 0;
	unsigned int index1 = 0;
	int row[10] = { -99,-1,-1,-1,-1,-1,-1,-1,-1 ,-1 };
	for (int i = 0; i < 9; ++i) {
		index1 = indexes[i];
		
		n = gamePiece_[index1].piece_displaced.at(0) - '0';

		// check it has confliction
		if (row[n] == -1) {
			row[n] = index1;
		}
		else if (row[n] == -99) {
			cout << "(" << gamePiece_[index1].x_ << "," << gamePiece_[index1].y_ << ") is blank, please check your algorithm" << endl;
			return false;
		}
		else {
			int index2 = row[n];
			cout << "(" << gamePiece_[index1].x_ << "," << gamePiece_[index1].y_ << ")  and ("
				<< gamePiece_[index2].x_ << "," << gamePiece_[index2].y_ << ") have confliction." << endl;
			cout << "please try again..";
			return false;
		}

	}
	return true;

}

// always return false since it's not used to judge the game condition
bool Sudoku::draw(){
	return true;
}

//no longer used
unsigned int Sudoku::suggest_for_X(){
	return 0;
}
//no longer used
unsigned int Sudoku::suggest_for_O(){		
	return 0;
}


// read from the user input and judge where it is a logical place 
int Sudoku::turn(){
	
	unsigned int index;
	unsigned int x;
	unsigned int y;
	unsigned int n;
	
	
	while (true) {
		int message = prompt(x, y, n);
		if (message == funReturn::ask_to_quit) {

			cout << "user quit" << endl;
			return funReturn::quit_the_game;

		}
		index = broadDimension_x*y + x;
		//if the piece is not placed by game
		if (!gamePiece_[index].placedbygame) {
			gamePiece_[index].x_ = x;
			gamePiece_[index].y_ = y;
			
			// n for to erase the piece
			if (n == 0) {
				if (gamePiece_[index].piece_displaced != "") {
					++number_of_blanks;
				}
				gamePiece_[index].piece_displaced = "";
	
			}
			else {
				if (gamePiece_[index].piece_displaced == ""){
					--number_of_blanks;
				}
				gamePiece_[index].piece_displaced = n+'0';
				

			}
			++number_of_played;
			return funReturn::success;

		}
		else {
			cout << "You can't replace the number at (" << x << ", " << y << "). Please input again." << endl;
		}

	}

}

void Sudoku::print(){cout<<*this<<endl;}