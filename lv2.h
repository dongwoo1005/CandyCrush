#ifndef __LV2_H__
#define __LV2_H__
#include "level.h"
#include "square.h"


class Lv2: public Level{

public:

	~Lv2();
	Board* initBoard(int seed);
	bool isComplete(int currScore, int moveCount);
	void setInitScore(int currScore);
	int getMovesLeft();
};

#endif
