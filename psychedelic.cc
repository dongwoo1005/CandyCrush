#include "psychedelic.h"
#include "square.h"
#include "board.h"
#include <iostream>
#include <sstream>
using namespace std;



Psychedelic::Psychedelic(){
    lock = '_';
    special = 'p';
    colour = '_';
    lockFlag = false;
}



Psychedelic::~Psychedelic(){}



Psychedelic::Psychedelic(int r, int c, char lock, char special, char colour, bool lockFlag){
    this->r = r;
    this->c = c;
    this->lock = lock;
    this->special = special;
    this->colour = colour;
    this->lockFlag = lockFlag;
}



void Psychedelic::crush(){
    int samecolour = 0;

	lockFlag = false;
    lock = '_';
    special = '_';
	char prevColour = colour;
    colour = '_';

    Board *board = Board::getInstance();
    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
			if (board->theBoard[i][j]->getColour() != '_'){	
				if (board->theBoard[i][j]->getColour() == prevColour){
//					cout << "crushing r c from psy: " << i << j << endl;
					board->theBoard[i][j]->crush();
					samecolour++;
				}
			}
        } // end for		
    } // end for
    int score = board->getScore();
    score = score + (4 * samecolour);
    board->boardScore(score);
	draw();
    td->notify(r,c,lock,special,colour);
}



void Psychedelic::draw(){
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
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, true, 4 , colour_integer);
        }else {
            xw->fillSquares(1+51*col, 1+51*row, 50,  50, false, 4 , colour_integer);
        }
    }
}
