#include "lv3.h"
#include "board.h"
#include "square.h"
#include "basic.h"
#include "lateral.h"
#include "upright.h"
#include "unstable.h"
#include "psychedelic.h"
#include <cstdlib>

using namespace std;

Lv3::~Lv3(){}

Board* Lv3::initBoard(int seed){

	Board* theBoard = Board::getInstance();
	theBoard->setDisplay(td);

	movesLeft = 10;

	// seed
	srand(seed);

	for (int r=0; r<10; ++r){
		for (int c=0; c<10; ++c){

			char lock = '_';

			// decide colour
			int	colourn = rand() % 6;
			char colour = colourn + '0';			
			
			/*
			// decide if locked
			int random = rand() % 100;	// probability of 20%
			if (random < 20){
				lock = 'l';
			}
			*/

			// Set the square accordingly
			Basic* basicSq = new Basic;
			theBoard->setSquareinBoard(r,c,basicSq,colour,lock);

			//theBoard[r][c]->setDisplay(td);
		} // end for
	} // end for
					
	return theBoard;
}


bool Lv3::isComplete(int currScore, int moveCount){
	int reqScore = 700; 
	return ((currScore - initScore) >= reqScore) && ((movesLeft - moveCount) >= 0); 
}

void Lv3::setInitScore(int currScore){
	initScore = currScore;
}

int Lv3::getMovesLeft(){
	return movesLeft;
}
