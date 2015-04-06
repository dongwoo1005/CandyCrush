#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "textdisplay.h"
#include <string>
#include "window.h"

class Board;

class Square{
protected:
	int r, c;
    char lock, special, colour;
	TextDisplay* td;
	Xwindow *xw;
    bool lockFlag;
    int count;
	char calledFrom;
	int match;
public:
	// ctor and dtor
    Square();
	virtual ~Square();

	// Setter
    void setSquares(int r, int c, char colour, char lock);
    void setDisplay(TextDisplay *t);
	void setWindow(Xwindow *xw);
	void lockSquares();
    void setCoords(int r, int c);
	void setCalledFrom(char special);
	void setMatch(int match); 
    void setColour_special();
  
	// Getter
    int getCoords_row();
    int getCoords_col();
	bool isLocked();
    char getSpecial();
    char getColour();
    int getCount();

	// virtual method for subclass squares
    virtual void crush() = 0;
	virtual void draw() = 0;
}; 

#endif
