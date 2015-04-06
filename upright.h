#ifndef __UPRIGHT_H__
#define __UPRIGHT_H__
#include "square.h"

class Upright: public Square{
public:
    Upright();
	~Upright();
    Upright(int r, int c, char lock, char special, char colour, bool lockFlag);
	void crush();
	void draw();
};

#endif
