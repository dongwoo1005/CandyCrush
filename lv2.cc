#include "lv2.h"
#include "board.h"
#include "square.h"
#include "basic.h"
#include "lateral.h"
#include "upright.h"
#include "unstable.h"
#include "psychedelic.h"
#include <cstdlib>

using namespace std;

Lv2::~Lv2(){
//	delete td;
}

Board* Lv2::initBoard(int seed){
	
	//Square* theBoard[10][10];

	Board* theBoard = Board::getInstance();
	theBoard->setDisplay(td);

	// seed
	srand(seed);

	for (int r=0; r<10; ++r){
		for (int c=0; c<10; ++c){

			char lock = '_';

			// decide colour
			int	colourn = rand() % 6;
			char colour = colourn + '0';			

			// decide if locked
			int random = rand() % 100;	// probability of 20%
			if (random < 20){
				lock = 'l';
			}

			// Set the square accordingly
			Basic* basicSq = new Basic;
			theBoard->setSquareinBoard(r,c,basicSq,colour,lock);

			//theBoard[r][c]->setDisplay(td);
		} // end for
	} // end for
					
	return theBoard;
}

bool Lv2::isComplete(int currScore){
	int reqScore = 500; 
	Board* board = Board::getInstance();
	for (int r=0; r<10; r++){
		for (int c=0; c<10; c++){
			if (board->theBoard[r][c]->isLocked()){
				return false;
			}
		}
	}
	return (currScore - initScore) >= reqScore;
}

void Lv2::setInitScore(int currScore){
	initScore = currScore;
}
