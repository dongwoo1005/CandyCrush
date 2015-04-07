#include "lv0.h"
#include <string>
#include <cstdlib>
using namespace std;

Lv0::~Lv0(){
//	delete td;
}

Board* Lv0::initBoard(int seed){
	string defaultFilename = "sequence.txt";
	Board* board = loadBoard(defaultFilename);
	if (board == NULL){
		cerr << "sequence.txt is missing. Terminating the program." << endl;
		exit (EXIT_FAILURE);
	}
	return board;
}

bool Lv0::isComplete(int currScore, int moveCount){
	int reqScore = 200;
	return (currScore - initScore) >= reqScore;
}

void Lv0::setInitScore(int currScore){
	initScore = currScore;
}


int Lv0::getMovesLeft(){
	return movesLeft;
}
