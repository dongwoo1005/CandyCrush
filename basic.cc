#include "basic.h"
#include "square.h"
#include "window.h"
#include <sstream>
#include <string>

using namespace std;

Basic::Basic(){
    lock = '_';
    special = '_';
    colour = '_';
    lockFlag = false;
	xw = xw;


}


Basic::~Basic(){}

Basic::Basic(int r, int c, char lock, char special, char colour, bool lockFlag){
    this->r = r;
    this->c = c;
    this->lock = lock;
    this->special = special;
    this->colour = colour;
    this->lockFlag = lockFlag;
}


void Basic::crush(){
//	cout << "crushing rc from basic: " << r << c << endl; 
    lockFlag = false;
	lock = '_';
    colour = '_';
	draw();
    td->notify(r,c,lock,special,colour);
}


void Basic::draw(){
	if (xw) {
		int colour_integer;
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
			xw->fillSquares(1+51*col, 1+51*row, 50, 50, true, 0, colour_integer);
		} else {
			xw->fillSquares(1+51*col, 1+51*row, 50, 50, false, 0 , colour_integer);
		}
	}
}
