#include "stdafx.h"
#include"gamePiece.h"
#include "ErrorCode.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctype.h>

gamePiece::gamePiece() : piece_color(piece_color::noColor), piece_name(" "), piece_displaced(" "), x_(0), y_(0),placedbygame(false){
	for (int i = 0; i < 8; ++i){
		adj[i] = -1;
	}
}

void computerADj(int *adj, int x, int y, int horizental, int vertical){
	int i = 0;
	for (int xi = -1; xi < 2; ++xi){
		for (int yi = -1; yi < 2; ++yi){
			if (!(xi == 0 && yi == 0)){
				int ax = xi + x;
				int ay = yi + y;
				if (ax >= 0 && ay >= 0 && ax < horizental &&ay < vertical){
					adj[i] = horizental*ay + ax;
					i++;
				}
			}
		}

	}

}


