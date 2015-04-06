#ifndef __STABLE_H__
#define __STABLE_H__
#include "square.h"

class Unstable: public Square{
public:
    Unstable();
	~Unstable();
    Unstable(int r, int c, char lock, char special, char colour, bool lockFlag);
	void crush();
	void draw();
	//void notify();
};

#endif
