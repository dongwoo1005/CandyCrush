#ifndef __LV2_H__
#define __LV2_H__
#include "level.h"
#include "square.h"


class Lv2: public Level{

public:

	~Lv2();
	Board* initBoard(int seed);
	bool isComplete(int currScore);
	void setInitScore(int currScore);
};

#endif
