#include "level.h"
#include "board.h"
#include "basic.h"
#include "lateral.h"
#include "upright.h"
#include "unstable.h"
#include "psychedelic.h"
#include <fstream>

using namespace std;

Level::~Level(){}

void Level::setDisplay(TextDisplay* t){
	td = t;
}

Board* Level::loadBoard(string filename){	

	ifstream file(filename.c_str());
	if (!file){
		return NULL;
	}
 
    Board* theBoard = Board::getInstance();
	theBoard->setDisplay(td);

	
	string asquare;
	for (int r=0; r<10; ++r){
		for(int c=0; c<10; ++c){
			file >> asquare;
			char lock = asquare[0];
			char type = asquare[1];
			char colour = asquare[2];					// Note:
			if (type == '_'){							// asquare[0] corresponds to lock
				// Create Basic square					// asquare[1] corresponds to type of square
				Basic* basicSq = new Basic;				// asquare[2] corresponds to colour
				theBoard->setSquareinBoard(r,c,basicSq,colour,lock);
			} else if (type == 'h'){
				// Create Lateral square
				Lateral* lateralSq = new Lateral;
				theBoard->setSquareinBoard(r,c,lateralSq,colour,lock);
			} else if (type == 'v'){
				// Create Upright square
				Upright* uprightSq = new Upright;
				theBoard->setSquareinBoard(r,c,uprightSq,colour,lock);
			} else if (type == 'b'){
				// Create Unstable square
				Unstable* unstableSq = new Unstable;
				theBoard->setSquareinBoard(r,c,unstableSq,colour,lock);
			} else if (type == 'p'){
				// Create Psychedelic square
				Psychedelic* psychedelicSq = new Psychedelic;
				theBoard->setSquareinBoard(r,c,psychedelicSq,colour,lock);
			}
		}
	}
	string genSeq;
	file >> genSeq;
	theBoard->setGenSequence(genSeq);
	return theBoard;
}

