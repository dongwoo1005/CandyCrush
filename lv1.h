#ifndef __LV1_H__
#define __LV1_H__
#include "board.h"
#include "level.h"

class Lv1: public Level{
public:

	~Lv1();
	Board* initBoard(int seed);
	bool isComplete(int currScore, int moveCount);	
	void setInitScore(int currScore);
	int getMovesLeft();
};

#endif
