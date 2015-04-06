#ifndef __LATERAL_H__
#define __LATERAL_H__
#include "square.h"

class Lateral: public Square{
public:
    Lateral(int r, int c, char lock, char special, char colour, bool lockFlag);
    Lateral();
	~Lateral();
	void crush();
	void draw();
	//void notify();
};

#endif
