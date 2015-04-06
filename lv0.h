#ifndef __LV0_H__
#define __LV0_H__
#include "board.h"
#include "level.h"

class Lv0: public Level{


public: 

	~Lv0();
	Board* initBoard(int seed);
	bool isComplete(int currScore);
	void setInitScore(int currScore);
};

#endif
