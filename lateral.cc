#include "lateral.h"
#include "square.h"
#include "board.h"
#include <iostream>
#include <sstream>
using namespace std;

Lateral::Lateral(int r, int c, char lock, char special, char colour, bool lockFlag){
    this->r = r;
    this->c = c;
    this->lock = lock;
    this->special = special;
    this->colour = colour;
    this->lockFlag = lockFlag;
}

Lateral::Lateral(){
    lock = '_';
    special = 'h';
    colour = '_';
    lockFlag = false;
}

Lateral::~Lateral(){}

void Lateral::crush(){
    Board* board = Board::getInstance();
	lockFlag = false;
    lock = '_';
    colour = '_';
    special = '_';
    for (int i=0; i<10; ++i){
		if (board->theBoard[r][i]->getColour() != '_'){	
			//cout << "crushing r c from lateral: " << r << i << endl;
			board->theBoard[r][i]->setCalledFrom('h');
			board->theBoard[r][i]->crush();
		}
    }
    int score = board->getScore();
	if (calledFrom != 'h'){
    	score = score + 40;
	}
    board->boardScore(score);
	draw();
    td->notify(r,c,lock,special,colour);
}


void Lateral::draw(){
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
		if (lockFlag){
			xw->fillSquares(1+51*col, 1+51*row, 50,  50, true, 1 , colour_integer);
		} else {
			xw->fillSquares(1+51*col, 1+51*row, 50,  50, false, 1 , colour_integer);	
		}
    }
}
