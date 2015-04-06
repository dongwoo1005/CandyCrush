#include <iostream>
#include "unstable.h"
#include "square.h"
#include "board.h"
#include <sstream>

using namespace std;

Unstable::Unstable(){
    lock = '_';
    special = 'b';
    colour = '_';
    lockFlag = false;
}

Unstable::~Unstable(){}

Unstable::Unstable(int r, int c, char lock, char special, char colour, bool lockFlag){
    this->r = r;
    this->c = c;
    this->lock = lock;
    this->special = special;
    this->colour = colour;
    this->lockFlag = lockFlag;
}

void Unstable::crush(){
    lock = '_';
	lockFlag = false;
    special = '_';
    colour = '_';
	int square = 0;

    Board *board = Board::getInstance();

	// When involved in 4 square match, create 5x5 hole
	if (match == 4){
		for (int i=r-2; i<=r+2; ++i){
			for (int j=c-2; j<=c+2; ++j){
				// crush if and only if it has not been crushed
				if ((i >= 0 && i < 10) && (j >= 0 && j < 10)){
					if (board->theBoard[i][j]->getColour() != '_'){	
//						cout << "crushing r c from unstable: " << i << j << endl;
						board->theBoard[i][j]->crush();
					}
				}
			}
		}
		square = 25;
	}
	else { // Default, create 3x3 hole
		for (int i=r-1; i<=r+1; ++i){
			for (int j=c-1; j<=c+1; ++j){
				// crush if and only if it has not been crushed
				if ((i >= 0 && i < 10) && (j >= 0 && j < 10)){
					if (board->theBoard[i][j]->getColour() != '_'){	
					//	cout << "crushing r c from unstable: " << i << j << endl;
						board->theBoard[i][j]->crush();
					}
				}
			}
		}
		square = 9;
	}
    int score = board->getScore();
    score = score + (square * 4);
    board->boardScore(score);
	draw();
    td->notify(r,c,lock,special,colour);
}

void Unstable::draw(){
  
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
            case '_':colour_integer = Xwindow::Black;break;
        }

        if (lockFlag){
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, true, 3 , colour_integer);
        } else {
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, false, 3 , colour_integer);
        }
    }
   
}
