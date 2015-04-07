#ifndef __BASIC_H__
#define __BASIC_H__
#include "square.h"

class Basic: public Square{

public:
    Basic();
	~Basic();
    Basic(int r, int c, char lock, char special, char colour, bool lockFlag); 
	void crush();
	void draw();
};

#endif
