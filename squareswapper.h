#ifndef __SQUARESWAPPER_H__
#define __SQUARESWAPPER_H__

#include "square.h"
#include "textdisplay.h"
#include "window.h"
#include "level.h"
#include <string>

class TextDisplay;

class SquareSwapper {
	Board* theBoard;
	int currLevel;
	Level* Lv;
	int currScore;
	int seed;
	int currMovesLeft; 		// advanced feature. not implemented yet
//	int hiScore; 			// advanced feature, not implemented yet
	TextDisplay* td;
	Xwindow* theWindow;
	bool testingModeON;
	int moveCount;
public:

	// ctor & dtor
	SquareSwapper();
	~SquareSwapper();

	// clears the memory regarding to the Board	
	void clearBoard();

	// initial configuration for the commandline options
	void init(int leveln,int seed, bool textOnlyMode, bool testingMode, std::string filename, bool bonus);

	// available command
	void swap(int x, int y, int z);
	bool hint(bool outputON);
	void scramble();
	void levelup();
	void leveldown();
	void restart();

	// core functions
    bool check(int x, int y);
    bool chainCheck(int x, int y, int count);
	void chainMatches();
    void dropSquares();
    void generateSquares(); 
	void removeMatches();
	void moveCountUp();

	// getter, setter, updater for score
    int returnScore();
	void getScore();
    void scoreUpdate();

	// testingMode methods
	void test();
	void turnTestON();

	// level completion method
	bool isLvComplete();

	// output operator for SquareSwapper
	friend std::ostream& operator<<(std::ostream& out, const SquareSwapper& b);	
};

#endif
