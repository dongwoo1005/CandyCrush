#ifndef __LV0_H__
#define __LV0_H__
#include "board.h"
#include "level.h"

class Lv0: public Level{


public: 

	~Lv0();
	Board* initBoard(int seed);
	bool isComplete(int currScore, int moveCount);
	void setInitScore(int currScore);
	int getMovesLeft();
};

#endif
