#include "squareswapper.h"
#include "lv0.h"
#include "lv1.h"
#include "lv2.h"
#include "lv3.h"
#include "textdisplay.h"
#include "window.h"
#include <iostream>
#include <cstdlib>
using namespace std;


// Ctor and Dtor
SquareSwapper::SquareSwapper():theBoard(NULL),currLevel(0),Lv(NULL),currScore(0),td(NULL),testingModeON(false){}

SquareSwapper::~SquareSwapper(){
	clearBoard();
	delete Lv;
	delete td;
}



// Clears the memory regarding to the Board
void SquareSwapper::clearBoard(){
	theBoard->clearBoard();
	theBoard->draw();
}



// Initial configuration for the commandline options
void SquareSwapper::init(int leveln, int seed, bool textOnlyMode, bool testingMode, string filename, bool bonus){
	td = new TextDisplay;

	this->seed = seed;

	currLevel = leveln;

	moveCount = 0;
	if (currLevel == 0){
		Lv = new Lv0;
	} else if (currLevel == 1){
		Lv = new Lv1;
	} else if (currLevel == 2){
		Lv = new Lv2;
	} else if (currLevel == 3){
		Lv = new Lv3;
	}else {
		cerr << "Invalid level is provided. We set it to Lv0" << endl;
		Lv = new Lv0;
	}
	Lv->setInitScore(currScore);
	Lv->setDisplay(td);

	if (!textOnlyMode){
		if (bonus) {
			theWindow = new Xwindow(1000, 520, 1);
			theBoard->setWindow(theWindow);
		}
		else {
			theWindow = new Xwindow(1000, 520, 0);
			theBoard->setWindow(theWindow);
		}
	}


	if (testingMode){
		testingModeON = true;
	}

	if (filename != ""){
		theBoard = Lv->loadBoard(filename);
		if (theBoard == NULL){
			theBoard = Lv->initBoard(seed);
		}
	} else {
		theBoard = Lv->initBoard(seed);
	}
	if (currLevel == 3){
		currMovesLeft = Lv->getMovesLeft();
	}
	theBoard->levelUpdate(currLevel);
    theBoard->movesUpdate(currMovesLeft);
	theBoard->draw();
}



// Available Commands
void SquareSwapper::swap(int x, int y, int z){
    theBoard->swap(x,y,z,true);
}



bool SquareSwapper::hint(bool outputON){
    return theBoard->hint(outputON);
}



void SquareSwapper::scramble(){
    theBoard->scramble();
}



void SquareSwapper::levelup(){
	if (currLevel == 0){
		currLevel++;
		theBoard->levelUpdate(currLevel);
        theBoard->movesUpdate(currMovesLeft);
		delete Lv;
		Lv = new Lv1;
		Lv->setInitScore(currScore);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
		theBoard->draw();
	}
	else if (currLevel == 1){
		currLevel++;
		theBoard->levelUpdate(currLevel);
		delete Lv;
		Lv = new Lv2;
		Lv->setInitScore(currScore);
        theBoard->movesUpdate(currMovesLeft);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
		theBoard->draw();
	} else if (currLevel == 2){	
		currLevel++;
		theBoard->levelUpdate(currLevel);
		delete Lv;
		Lv = new Lv3;
		Lv->setInitScore(currScore);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
		currMovesLeft = Lv->getMovesLeft();
        theBoard->movesUpdate(currMovesLeft);
		theBoard->draw();
	}
	else if (currLevel == 3){
		cerr << "You are at the Highest Level!" << endl;
	}
}



void SquareSwapper::leveldown(){
	if (currLevel == 0){
		cerr << "You are at the Lowest Level!" << endl;
	}
	else if (currLevel == 1){
		currLevel--;
		theBoard->levelUpdate(currLevel);
		delete Lv;
		Lv = new Lv0;
		Lv->setInitScore(currScore);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
        theBoard->movesUpdate(currMovesLeft);
		theBoard->draw();
	}
	else if (currLevel == 2){
		currLevel--;
		theBoard->levelUpdate(currLevel);
		delete Lv;
		Lv = new Lv1;
		Lv->setInitScore(currScore);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
        theBoard->movesUpdate(currMovesLeft);
		theBoard->draw();
	} else if (currLevel == 3){
		currLevel--;
		theBoard->levelUpdate(currLevel);
		delete Lv;
		Lv = new Lv2;
		Lv->setInitScore(currScore);
		clearBoard();
		Lv->setDisplay(td);
		theBoard = Lv->initBoard(seed);
        theBoard->movesUpdate(currMovesLeft);
		theBoard->draw();
	}
}



void SquareSwapper::restart(){

	if (currLevel == 3){
        clearBoard();
        moveCount = 0;
        Lv->setInitScore(currScore);
        theBoard = Lv->initBoard(seed);
        currMovesLeft = Lv->getMovesLeft();
    } else {
        clearBoard();
        currScore = 0;
        moveCount = 0;
        currMovesLeft = 0;
        Lv->setInitScore(currScore);
        theBoard = Lv->initBoard(seed);
    }
	theBoard->levelUpdate(currLevel);
    theBoard->movesUpdate(currMovesLeft);
	theBoard->updatemoves_count(moveCount);
	scoreUpdate();
	theBoard->draw();
}






// Core functions
bool SquareSwapper::check(int x, int y){
    scoreUpdate();
    bool ans = false;
    if ((theBoard->checkBasic(x,y)) || (theBoard->checkPsy(x,y)) || (theBoard->checkUnstable(x,y)) ||
        (theBoard->checkVertical(x,y)) || (theBoard->checkLateral(x, y))){
        ans = true;
        getScore();
    }
    return ans;
}



bool SquareSwapper::chainCheck(int i, int j, int count){
    bool ans = false;
    scoreUpdate();
    if (ans == false && theBoard->checkBasic(i,j)){
        ans = true;
        currScore = (count*2*(returnScore() - currScore))+currScore;
        scoreUpdate();
    }if (ans == false && theBoard->checkLateral(i,j)){
        ans = true;
        currScore = (count*2*(returnScore() - currScore))+currScore;
        scoreUpdate();
    }if (ans == false && theBoard->checkPsy(i,j)){
        ans = true;
        currScore = (count*2*(returnScore() - currScore))+currScore;
        scoreUpdate();
    }if (ans == false && theBoard->checkVertical(i,j)){
        ans = true;
        currScore = (count*2*(returnScore() - currScore))+currScore;
        scoreUpdate();
    }if (ans == false && theBoard->checkUnstable(i,j)){
        ans = true;
        currScore = (count*2*(returnScore() - currScore))+currScore;
        scoreUpdate();
    }
    return ans;
}



void SquareSwapper::chainMatches(){
	bool newGen = false;
	bool droppedCheck = true;
	int count = 1;
	while (droppedCheck || newGen){
	
		bool matchFound = false;

		// Check Matches and crush if there is
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				if (chainCheck(i,j, count)){
					count++;
					matchFound = true;
				} // end if
			} // endfor
		} // end for

		// If match is found and crushed, drop the squares
		if (matchFound){
			if (testingModeON) { test(); }	// print board with crushed squares
			dropSquares();					// drop the upper squares
			droppedCheck = true;
			if (testingModeON) { test(); }	// print board with dropped squares
		} // end if 

		else {
			if (newGen){				// if match is not found from fully filled board
				newGen = false;			// stop the chain reaction
			}
			else if (droppedCheck){		// if match is not found from partially empty board
				generateSquares();		// generate new squares
				newGen = true;
				droppedCheck = false;
				if (testingModeON) { test(); }	// print board with genereated squares
			}
		} // end else
	}
	theBoard->draw();
}



void SquareSwapper::dropSquares(){
    theBoard->dropSquares();
}



void SquareSwapper::generateSquares(){
    theBoard->generateSquares();
}



void SquareSwapper::removeMatches(){
	bool wasThereMatch = false;
	bool firstIter = true;
	while (firstIter || wasThereMatch){
		firstIter = false;
		wasThereMatch = false;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				bool ans = chainCheck(i,j,0);
				wasThereMatch = wasThereMatch || ans;
				if (ans == true){
					dropSquares();
					//ans = chainCheck(i,j,0);
					generateSquares();
					//ans = chainCheck(i,j,0);
					wasThereMatch = true;
				}
			}
		}
	}
}



void SquareSwapper::moveCountUp(){
	moveCount++;
    theBoard->updatemoves_count(moveCount);
}

 
// getter, setter, updater for score
int SquareSwapper::returnScore(){
    return theBoard->getScore();
}



void SquareSwapper::getScore(){
    currScore = theBoard->getScore();
}



void SquareSwapper::scoreUpdate(){
    theBoard->boardScore(currScore);
}



// testingMode methods
void SquareSwapper::test(){
	if (testingModeON){
		theBoard->draw();
		cout << *this;
		cout << "Type next to draw the next step" << endl;
		string command;
		bool done = false;
		while(!done){
			cin >> command;
			if (cin.fail()){
				if (cin.eof()){
					exit(EXIT_FAILURE);
				}
				break;
			}
			if ( command == "next"){
				done = true;
			} else if (command == "continue"){
				testingModeON = false;
				done = true;
			} else {
				cerr << "Valid commands are: next, continue" << endl;
			}
		}
	}
}



void SquareSwapper::turnTestON(){
	testingModeON = true;
}



// level completion method
bool SquareSwapper::isLvComplete(){
	if (moveCount == currMovesLeft){
		cout << "Out of Moves. Restarting." << endl;
		restart();
	} 
	return Lv->isComplete(currScore,moveCount);
}



// output operator for SquareSwapper
ostream& operator<<(ostream& out, const SquareSwapper& b){
	out << "Level: " << b.currLevel << endl;
	out << "Score: " << b.currScore << endl;
	if (b.currMovesLeft == 0) {
		out << "Moves Remaining: Unlimited" << endl;
	} else {
		out << "Moves Remaining: " << b.currMovesLeft - b.moveCount << endl; // advanced feature
	}
//	out << "Hi Score: " << hiScore << endl;			 	 // advanced feature
	out << "----------" << endl;
	out << *b.td;
	return out;	
}

