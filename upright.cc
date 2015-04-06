#include "upright.h"
#include "board.h"
#include <iostream>
#include <sstream>
using namespace std;


Upright::Upright(){
    lock = '_';
    special = 'v';
    colour = '_';
    lockFlag = false;
}


Upright::~Upright(){}

Upright::Upright(int r, int c, char lock, char special, char colour, bool lockFlag){
    this->r = r;
    this->c = c;
    this->lock = lock;
    this->special = special;
    this->colour = colour;
    this->lockFlag = lockFlag;
}




void Upright::crush(){
    Board *board = Board::getInstance();
	lockFlag = false;
    lock = '_';
    colour = '_';
    special = '_';


    for (int i=0; i < 10; ++i) {
		if (board->theBoard[i][c]->getColour() != '_'){	
//			cout << "crushing r c from upright: " << i << c << endl;
			board->theBoard[i][c]->setCalledFrom('v');
			board->theBoard[i][c]->crush();
		}
    }

    int score = board->getScore();
	if (calledFrom != 'v'){
    	score = score + 40;
	}
    board->boardScore(score);
	draw();
    td->notify(r,c,lock,special,colour);
}

void Upright::draw(){
	if (xw) {
		int colour_integer;
		stringstream ss;
		string s;
		ss << special;
		ss >> s;
		int row = this->r;
		int col = this->c;
		switch (colour){
			case '0': colour_integer = Xwindow::White;break;
			case '1': colour_integer = Xwindow::Red;break;
			case '2': colour_integer = Xwindow::Green;break;
			case '3': colour_integer = Xwindow::Blue;break;
			case '4': colour_integer = Xwindow::Cyan;break;
			case '5': colour_integer = Xwindow::Yellow;break;
			case '_': colour_integer = Xwindow::Black;break;
		}
        xw->fillRectangle(1+51*col, 1+51*row, 50,  50, colour_integer); 

		if (lockFlag){
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, true, 2 , colour_integer);
        } else {
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, false, 2 , colour_integer);
        }

/*
		if (special != '_'){
			xw->drawBigString(1+51*col, 1+51*row+50, s, Xwindow::Black);
		}
		if (lockFlag) {
			string lockString = "l";
			xw->drawBigString(1+51*col, 1+51*row+50, lockString, Xwindow::Black);
		}
*/
    }
    
}




