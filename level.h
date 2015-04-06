#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include "board.h"

class Level{
protected:
	int initScore;
	TextDisplay* td;
public:
	// dtor
	virtual ~Level();

	// method to initiate the board from reading a file
	Board* loadBoard(std::string filename);

	//  virtual methods
	virtual Board* initBoard(int seed) = 0;
	virtual bool isComplete(int currScore) = 0;
	virtual void setInitScore(int currScore) = 0;
	virtual void setDisplay(TextDisplay* t);
};

#endif
