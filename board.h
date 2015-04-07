#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "window.h"
#include <string>

class Board{
	TextDisplay* td;
    std::string genSequence;
    int score;
	int level;
    int moves;
    int moves_count;
    static Board *instance;
	static Xwindow *xw;
public:
	Square* theBoard[10][10];

	// Singleton Board methods
    static Board* getInstance();
    static void cleanup();

	// Clear all the memories allocated for each Squares in the Baord
	void clearBoard();

	// Setter for Displays (text + graphic)
	void setDisplay(TextDisplay* t);
	void setWindow(Xwindow *x);

	// Draw method to graphically display Level and Score
	void draw();

	// Basic Command feature implementations
	void swap(int x, int y, int z, bool outputON);
	void scramble();
    bool hint(bool outputON);


	// Helper Function to determine the number of same colour in the following direction
    int checkVmatch_up(int x, int y);
    int checkVmatch_down(int x, int y);
    int checkHmatch_left(int x, int y);
    int checkHmatch_right(int x, int y);


	// Core Functions
    bool checkBasic(int x, int y);
    bool checkLateral(int x, int y);
    bool checkVertical(int x, int y);
    bool checkUnstable(int x, int y);
    bool checkPsy(int x, int y);
    void dropSquares();
    void generateSquares();

	// Setters
	void levelUpdate(int currLevel);
    void movesUpdate(int moves);
    void boardScore(int currScore);
	void setGenSequence(std::string genSeq);
    void updatemoves_count(int moves_count);

	// Getter
    int getScore();

	// Setters for Squares in Board
	void setSquareinBoard(int r, int c, Square* sq, char colour, char lock);	
	void lockSquare(int r, int c);


};

#endif
