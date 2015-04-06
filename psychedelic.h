#ifndef __PSYCHEDELIC_H__
#define __PSYCHEDELIC_H__
#include "square.h"

class Psychedelic: public Square{
public:
    Psychedelic();
	~Psychedelic();    
    Psychedelic(int r, int c, char lock, char special, char colour, bool lockFlag);

	void crush();
	void draw();
};

#endif
