#include "lv1.h"
#include "square.h"
#include "basic.h"
#include "lateral.h"
#include "upright.h"
#include "unstable.h"
#include "psychedelic.h"
#include "board.h"
#include <cstdlib>
using namespace std;

Lv1::~Lv1(){
	//delete td;

}

Board* Lv1::initBoard(int seed){

//	Square* theBoard[10][10];

	Board* theBoard = Board::getInstance();
	theBoard->setDisplay(td);

	// seed
	srand(seed);

	for (int r=0; r<10; ++r){
		for (int c=0; c<10; ++c){

			char colour;
			int colourn;
			int type;
			char lock = '_';

			// decide colour
			int random = rand() % 12;
			if (random < 6){				// probability of 6/12 to choose red or white
				colourn = rand() % 2;		// White or Red (1/2 probability)
			}
			else if (random < 10){			// probability of 4/12 to choose green or blue
				colourn = 2 + rand() % 2;	// Green or Blue (1/2 probability)
			}
			else if (random < 12){			// probability of 2/12 to choose cyan or yellow
				colourn = 4 + rand() % 2;	// Cyan or Yellow (1/2 probability)
			}

			colour = colourn + '0';

			// decide type of square
			random = rand() % 20;
			if (random == 0){					// probability of 1/20 (5%)
				type = 1 + rand() % 4;			// 1 - Lateral, 2 - Upright, 3 - Unstable, 4 - Psychedelic
			} else {
				type = 0;						// 0 - Basic
			}

			// Create the Square accordingly
			if (type == 0){	
				// Create Basic square					
				Basic* basicSq = new Basic;
				theBoard->setSquareinBoard(r,c,basicSq,colour,lock);
			} else if (type == 1){
				// Create Lateral square
				Lateral* lateralSq = new Lateral;
				theBoard->setSquareinBoard(r,c,lateralSq,colour,lock);
			} else if (type == 2){
				// Create Upright square
				Upright* uprightSq = new Upright;
				theBoard->setSquareinBoard(r,c,uprightSq,colour,lock);
			} else if (type == 3){
				// Create Unstable square
				Unstable* unstableSq = new Unstable;
				theBoard->setSquareinBoard(r,c,unstableSq,colour,lock);
			} else if (type == 4){
				// Create Psychedelic square
				Psychedelic* psychedelicSq = new Psychedelic;
				theBoard->setSquareinBoard(r,c,psychedelicSq,colour,lock);
			}			
		} // end for
	} // end for

	

	return theBoard;
}

bool Lv1::isComplete(int currScore, int moveCount){
	int reqScore = 300;
	return (currScore - initScore) >= reqScore;
}

void Lv1::setInitScore(int currScore){
	initScore = currScore;
}

int Lv1::getMovesLeft(){
	return movesLeft;
}
