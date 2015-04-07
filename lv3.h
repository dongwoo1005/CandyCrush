#ifndef __LV3_H__
#define __LV3_H__
#include "level.h"
#include "square.h"


class Lv3: public Level{

public:

	~Lv3();
	Board* initBoard(int seed);
	bool isComplete(int currScore, int moveCount);
	void setInitScore(int currScore);
	int getMovesLeft();
};

#endif
