#include "textdisplay.h"
#include "square.h"
#include <string>

using namespace std;

// ctor and dtor
Square::Square(){}

Square::~Square(){}



// Setters
void Square::setSquares(int r, int c, char colour, char lock){
    this->r = r;
    this->c = c;
    this->colour = colour;
	if (lock == 'l'){
		lockFlag = true;
	}
    td->notify(r,c,lock, special, colour);
}

void Square::setDisplay(TextDisplay *t){
    td = t;
}

void Square::setWindow(Xwindow* x){
	xw = x;	
}

void Square::lockSquares(){
    lockFlag = true;
	lock = 'l';
    td->notify(r,c, lock, special, colour);
}

void Square::setCoords(int r, int c){
    this->r = r;
    this->c = c;
	td->notify(r,c,lock,special,colour);
}

void Square::setCalledFrom(char calledSq){
	calledFrom = calledSq;
}

void Square::setMatch(int match){
	this->match = match;
}

void Square::setColour_special(){
    colour = '_';
    special = '_';
}



// Getters
int Square::getCoords_row(){
    return r;
}

int Square::getCoords_col(){
    return c;
}

bool Square::isLocked(){
	return lockFlag;
}

char Square::getSpecial(){
    return special;
}

char Square::getColour(){
    return colour;
}

int Square::getCount(){
    return count;
}
