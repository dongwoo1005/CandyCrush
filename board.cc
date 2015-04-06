#include "board.h"
#include <iostream>
#include <algorithm>	// random_shuffle
#include <vector>
#include <ctime>		// time
#include "square.h"
#include "basic.h"
#include "upright.h"
#include "lateral.h"
#include "psychedelic.h"
#include "unstable.h"
#include "window.h"

using namespace std;

// Set the static Board instance and Xwindow Display to NULL
Xwindow* Board::xw = NULL;
Board *Board::instance = 0;



// Singleton Board Methods
Board* Board::getInstance(){
    if (instance == NULL){
        instance = new Board;
        atexit(cleanup);
    }
    return instance;
}

void Board::cleanup(){
    delete instance;
}



// Clear all the memories allocated for each Squares in the Baord
void Board::clearBoard(){
	for (int r=0; r<10; ++r){
		for (int c=0; c<10; ++c){
			delete theBoard[r][c];
		}
	}
}



// Setter for Displays (text + graphic)
void Board::setDisplay(TextDisplay* t){
	td = t;
}

void Board::setWindow(Xwindow *x){
	this->xw = x;
}



// Draw method to graphically display Level and Score
void Board::draw(){
    if (xw){
        xw->drawAccessory(700,200, level, score, Xwindow::Black);
    }
}



// Basic Command feature implementations: swap, scramble, hint

void Board::swap(int x, int y, int z, bool outputON){

	// z direction: 0 for north, 1 for south, 2 for west, 3 for east
	if (!theBoard[x][y]->isLocked()){
		// NORTH
		if ((z == 0 && x > 0) && !theBoard[x-1][y]->isLocked()) {
				Square* temp = theBoard[x][y];
				theBoard[x][y] = theBoard[x-1][y];
				theBoard[x][y]->setCoords(x,y);
				if (outputON){ theBoard[x][y]->draw(); }
				theBoard[x-1][y] = temp;
				theBoard[x-1][y]->setCoords(x-1,y);
				if (outputON){ theBoard[x-1][y]->draw(); }
		} // end if

		// SOUTH
		else if ((z == 1 && x < 9) && !theBoard[x+1][y]->isLocked()){
				swap (x+1, y, 0, outputON);
		} // end else if

		// WEST
		else if ((z == 2 && y > 0) && !theBoard[x][y-1]->isLocked()){
				Square* temp = theBoard[x][y];
				theBoard[x][y] = theBoard[x][y-1];
				theBoard[x][y]->setCoords(x,y);
				if (outputON) { theBoard[x][y]->draw();}
				theBoard[x][y-1] = temp;
				theBoard[x][y-1]->setCoords(x,y-1);
				if (outputON) { theBoard[x][y-1]->draw();}
		}

		// EAST
		else if ((z == 3 && y < 9) && !theBoard[x][y+1]->isLocked()){
				swap (x, y+1, 2, outputON);
		} // end else if

		// Invalid otherwise
		else {
		//	cerr << "Invalid swap" << endl;
		} // end else

	} // end if 
	else {
		//cerr << "Invalid swap" << endl;
	} // end else

} // end swap



void Board::scramble(){

	// Create two vectors to store new coordinates    
    vector <int> newr;
    vector <int> newc;
    
	// Stores applciable coordinates in order
    for (int i = 0; i < 10; i++){
        newr.push_back(i);
        newc.push_back(i);
    } // end for
 
	// Shuffle the vectors in random order
    srand ((unsigned)time(NULL));
    random_shuffle(newr.begin(), newr.end());
    random_shuffle(newc.begin(), newc.end());
    
	// Swap the Square at (r,c) with the Square at (nr,nc)
    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
				int nr = newr.at(r);
				int nc = newc.at(c);
			    Square* temp = theBoard[r][c];
                theBoard[r][c] = theBoard[nr][nc];
                theBoard[r][c]->setCoords(r, c);
				if (theBoard[r][c]->isLocked()) { theBoard[r][c]->lockSquares(); }
				theBoard[r][c]->draw();
                theBoard[nr][nc] = temp;
                theBoard[nr][nc]->setCoords(nr, nc);
				if (theBoard[nr][nc]->isLocked()) { theBoard[nr][nc]->lockSquares(); }
				theBoard[nr][nc]->draw();
        } // end for
    } // end for

} // end scramble




bool Board::hint(bool outputON){

    bool ans = false;

    for (int i = 0; i < 10; i++){			// Each Rows
        for (int j = 0; j < 10; j++){		// Each Cols
            for (int z = 0; z < 4; z++){	// Each Directions
				
				// If direction is North and the square is not locked
                if ((z == 0 && i > 0) && !theBoard[i][j]->isLocked()){	

                    swap(i,j,z,false);		// swap it without drawing

					// Check if match exists horizontally and vertically
                    int check_h = checkHmatch_right(i, j) + checkHmatch_left(i, j);		
                    int check_v = checkVmatch_down(i, j) + checkVmatch_up(i, j);

					// if found one of
                    if ( (check_v == 2  || check_h == 2)  || 	// Basic 3-match
						 (check_h == 3) ||						// Horizontal 4-match
                         ((check_h == 2 && check_v == 2)  || 	// L-match
						  (check_h == 3 && check_v == 3)) ||
						 (check_h == 4  || check_v == 4)  || 	// Horizontal or Vertical 5-match
						 (check_v == 3) ){						// Vertical 4-match

                        ans = true;

						// if this method is used for hint command, print out the hint
						if (outputON){
                        	cout << "swap " << i << " and " << j << " to " << z << "(North) direction" << endl;
						} // end if

                        swap(i-1,j,1,false);	// swap it back without drawing
                        return ans;				// return true;
                    } // end if
					else{
                        swap(i,j,0,false);	// swap it back without drawing
                    } // end else
                } // end if
 
				// If direction is South and the square is not locked
				else if ((z == 1 && i < 10) && !theBoard[i][j]->isLocked()){

                    swap(i,j,z,false);		// swap it without drawing

					// Check if match exists horizontally and vertically
                    int check_h = checkHmatch_right(i, j) + checkHmatch_left(i, j);		
                    int check_v = checkVmatch_down(i, j) + checkVmatch_up(i, j);

					// if found one of
                    if ( (check_v == 2  || check_h == 2)  || 	// Basic 3-match
						 (check_h == 3) ||						// Horizontal 4-match
                         ((check_h == 2 && check_v == 2)  || 	// L-match
						  (check_h == 3 && check_v == 3)) ||
						 (check_h == 4  || check_v == 4)  || 	// Horizontal or Vertical 5-match
						 (check_v == 3) ){						// Vertical 4-match

                        ans = true;

						// if this method is used for hint command, print out the hint
						if (outputON){
                        	cout << "swap " << i << " and " << j << " to " << z << "(South) direction" << endl;
						} // end if

                        swap(i,j,1,false);		// swap it back without drawing
                        return ans;				// return true
                    } // end if
					else {
                        swap(i,j,1,false);		// swap it back without drawing
                    } // end else
                } // end else if 
				
				// If direction is West and the square is not locked
				else if ((z == 2 && j > 0) && !theBoard[i][j]->isLocked()){

                    swap(i,j,z,false);		// swap it without drawing

					// Check if match exists horizontally and vertically
                    int check_h = checkHmatch_right(i, j) + checkHmatch_left(i, j);		
                    int check_v = checkVmatch_down(i, j) + checkVmatch_up(i, j);

					// if found one of
                    if ( (check_v == 2  || check_h == 2)  || 	// Basic 3-match
						 (check_h == 3) ||						// Horizontal 4-match
                         ((check_h == 2 && check_v == 2)  || 	// L-match
						  (check_h == 3 && check_v == 3)) ||
						 (check_h == 4  || check_v == 4)  || 	// Horizontal or Vertical 5-match
						 (check_v == 3) ){						// Vertical 4-match

                        ans = true;

						// if this method is used for hint command, print out the hint
						if (outputON){
                        	cout << "swap " << i << " and " << j << " to " << z << "(West) direction" << endl;
						} // end if

                        swap(i,j,2,false);		// swap it back without drawing
                        return ans;				// return true
                    } // end if
					else {
                        swap(i,j,2,false);
                    } // end else
                } // end else if

				// If direction is East and the square is not locked
				else if ((z == 3 && j < 10) && !theBoard[i][j]->isLocked()){

                    swap(i,j,z,false);		// swap it without drawing

					// Check if match exists horizontally and vertically
                    int check_h = checkHmatch_right(i, j) + checkHmatch_left(i, j);		
                    int check_v = checkVmatch_down(i, j) + checkVmatch_up(i, j);

					// if found one of
                    if ( (check_v == 2  || check_h == 2)  || 	// Basic 3-match
						 (check_h == 3) ||						// Horizontal 4-match
                         ((check_h == 2 && check_v == 2)  || 	// L-match
						  (check_h == 3 && check_v == 3)) ||
						 (check_h == 4  || check_v == 4)  || 	// Horizontal or Vertical 5-match
						 (check_v == 3) ){						// Vertical 4-match

                        ans = true;

						// if this method is used for hint command, print out the hint
						if (outputON){
                        	cout << "swap " << i << " and " << j << " to " << z << "(East) direction" << endl;
						} // end if

                        swap(i,j,3,false);		// swap it back without drawing
                        return ans;				// return true
                    } // end if
					else {
                        swap(i,j,3,false);
                    } // end else
                } // end else if

            } // end for
        } // end for
    } // end for
    return ans;									// return false
} // end hint



// Helper Functions to determine the number of Same Colour Squares in the following direction
int Board::checkVmatch_up(int x, int y){
    int count = 0;
    int r = theBoard[x][y]->getCoords_row();
    if (r > 0){
        for (int i = r - 1; i >= 0; i--){
            if ((theBoard[i][y]->getColour() == theBoard[x][y]->getColour()) &&
                (theBoard[i][y]->getColour() != '_')){
                count++;
            }else {
                break;
            }
        }
    }
    return count;
}



int Board::checkVmatch_down(int x, int y){
    int count = 0;
    int r = theBoard[x][y]->getCoords_row();
    if (r < 9){
        for (int i = r + 1; i < 10; i++){
            if ((theBoard[i][y]->getColour() == theBoard[x][y]->getColour()) &&
                (theBoard[i][y]->getColour() != '_')){
                count++;
            }else {
                break;
            }
        }
    }
    return count;
}



int Board::checkHmatch_left(int x, int y){
    int count = 0;
    int c = theBoard[x][y]->getCoords_col();
    if (c > 0){
        for (int i = c - 1; i >= 0; i--){
            if ((theBoard[x][i]->getColour() == theBoard[x][y]->getColour()) &&
                (theBoard[x][i]->getColour() != '_')){
                count++;
            }else {
                break;
            }
        }
    }
    return count;
}




int Board::checkHmatch_right(int x, int y){
    int count = 0;
    int c = theBoard[x][y]->getCoords_col();
    if (c < 9){
        for (int i = c + 1; i < 10; i++){
            if ((theBoard[x][i]->getColour() == theBoard[x][y]->getColour()) &&
            (theBoard[x][i]->getColour() != '_')){
                count++;
            }else {
                break;
            }
        }
    }
    return count;
}



// Core Functions
bool Board::checkBasic(int x, int y){	// check for both vertical and horizontal 3-match
    bool ans = false;
    int check_h = checkHmatch_left(x,y) + checkHmatch_right(x,y);
    int check_v = checkVmatch_down(x,y) + checkVmatch_up(x,y);
    if ((check_v == 2 && check_h != 2) || (check_h == 2 && check_v != 2)){
        ans = true;
        score = score + 3;
        int i = checkHmatch_left(x,y);
        int j = checkHmatch_right(x,y);
        int k = checkVmatch_down(x,y);
        int l = checkVmatch_up(x,y);
        if (check_h == 2){
            while (i > 0){
                theBoard[x][y-i]->crush();
                i--;
            }
            while (j > 0){
                theBoard[x][y+j]->crush();
                j--;
            }
        } else {
            while (k > 0){
                theBoard[x+k][y]->crush();
                k--;
            }
            while (l > 0){
                theBoard[x-l][y]->crush();
                l--;
            }
 
        }
        theBoard[x][y]->crush();
    }
    return ans;
}




bool Board::checkLateral(int x, int y){			// Check for Horizontal 4-match
    char colour= theBoard[x][y]->getColour();
	char special = theBoard[x][y]->getSpecial();
    bool ans = false;

    int left = checkHmatch_left(x,y);
    int right = checkHmatch_right(x,y);
//	horizontal = left + right;
    if (left + right == 3){
        ans = true;

        while (left > 0){
			theBoard[x][y - left]->setMatch(4);
            theBoard[x][y - left]->crush();
            left--;
        }

        while (right > 0){
			theBoard[x][y + right]->setMatch(4);
            theBoard[x][y + right]->crush();
            right--;
        }
        if (special != '_'){
			theBoard[x][y]->setMatch(4);
            theBoard[x][y]->crush();
        }
        delete theBoard[x][y];
        Lateral *lateral = new Lateral;
        setSquareinBoard(x,y,lateral,colour,'_');
    }
    return ans;
}




bool Board::checkVertical(int x, int y){			// Check for Vertical 4-match
    char colour = theBoard[x][y]->getColour();
	char special = theBoard[x][y]->getSpecial();
    bool ans = false;
    int down = checkVmatch_down(x,y);
    int up = checkVmatch_up(x,y);
//	vertical = down + up;
    if (down + up == 3){
        ans = true;
        while (down > 0){
			theBoard[x + down][y]->setMatch(4);
            theBoard[x + down][y]->crush();
			down--;
        }
        while (up > 0){
			theBoard[x - up][y]->setMatch(4);
            theBoard[x - up][y]->crush();
            up--;
        }
        if (special != '_'){
			theBoard[x][y]->setMatch(4);
            theBoard[x][y]->crush();
        }
        delete theBoard[x][y];
        Upright *upright = new Upright;
        setSquareinBoard(x,y,upright,colour,'_');
		score = score + (2 * 4);
    }
    return ans;
}



bool Board::checkUnstable(int x, int y){			// Check for L-matches
    char colour= theBoard[x][y]->getColour();
	char special = theBoard[x][y]->getSpecial();
    bool ans = false;
    int check_h = checkHmatch_left(x,y) + checkHmatch_right(x,y);
    int check_v = checkVmatch_down(x,y) + checkVmatch_up(x,y);
    if ((check_h == 2 && check_v == 2) || (check_h == 3 && check_v == 3)){
        ans = true;
        if (check_h == 2){
            score = score + (3 * 5);
        }if (check_h == 3){
            score = score + (4 * 7);
        }
        int i = checkHmatch_left(x,y);
        int j = checkHmatch_right(x,y);
        int k = checkVmatch_down(x,y);
        int l = checkVmatch_up(x,y);
        while (i > 0){
            theBoard[x][y-i]->crush();
            i--;
        }
        while (j > 0){
            theBoard[x][y+j]->crush();
            j--;
        }
        while (k > 0){
            theBoard[x+k][y]->crush();
            k--;
        }
        while (l > 0){
            theBoard[x-l][y]->crush();
            l--;
        }
        if (special != '_'){
            theBoard[x][y]->crush();
        }
        delete theBoard[x][y];
        Unstable *unstable = new Unstable;
        setSquareinBoard(x,y,unstable,colour,'_');
    }
    return ans;
}



bool Board::checkPsy(int x, int y){				// Check for 5-match
    
    char colour= theBoard[x][y]->getColour();
	char special = theBoard[x][y]->getSpecial();
	bool ans = false;
    int check_h = checkHmatch_left(x,y) + checkHmatch_right(x,y);
    int check_v = checkVmatch_down(x,y) + checkVmatch_up(x,y);
    if (check_h == 4 || check_v == 4){
        ans = true;
        int i = checkHmatch_left(x,y);
        int j = checkHmatch_right(x,y);
        int k = checkVmatch_down(x,y);
        int l = checkVmatch_up(x,y);
        if (check_h == 4){
            while (i > 0){
				theBoard[x][y-i]->setMatch(4);
                theBoard[x][y-i]->crush();
                i--;
            }
            while (j > 0){
				theBoard[x][y+j]->setMatch(4);
                theBoard[x][y+j]->crush();
                j--;
            }
            
        }else {
            while (k > 0){
				theBoard[x+k][y]->setMatch(4);
                theBoard[x+k][y]->crush();
                k--;
            }
            while (l > 0){
				theBoard[x-1][y]->setMatch(4);
                theBoard[x-l][y]->crush();
                l--;
            }
        }
        if (special != '_'){
            theBoard[x][y]->crush();
        }
        delete theBoard[x][y];
        Psychedelic *psy = new Psychedelic;
        setSquareinBoard(x,y,psy,colour,'_'); score = score + (3 * 5);
    }
    return ans;
}




void Board::dropSquares(){
    for (int c=0; c<10; ++c){
        vector <Square*> validSquares;
        for (int r=9; r>=0; --r){
            if (theBoard[r][c]->getColour()!='_'){	// if the square is valid, put it into validSquares vector
                validSquares.push_back(theBoard[r][c]);
            }
        }

        int r = 9;
        for (unsigned int i=0; i < validSquares.size(); ++i){
            if (theBoard[r][c]->getColour()=='_'){ // if the square at r,c  is crushed then swap it with the valid square
                Square* temp = theBoard[r][c];
                theBoard[r][c] = validSquares.at(i);
                int prevr = theBoard[r][c]->getCoords_row();
                theBoard[r][c]->setCoords(r,c);
				theBoard[r][c]->draw();
                theBoard[prevr][c] = temp;
                theBoard[prevr][c]->setCoords(prevr,c);
				theBoard[prevr][c]->draw();
            }
            r--;
        }
    }
}




void Board::generateSquares(){
    int len = genSequence.length();
    int i = 0;
    for (int c = 0; c < 10; ++c){
        for (int r = 9; r >= 0; --r){
            
            if (theBoard[r][c]->getColour() == '_'){
                char colour = '_';
                char lock = '_';
                
                if (genSequence == ""){
                    int colourn = rand() % 6;
                    colour = colourn + '0';
                } else {
                    if (i == len) {	i = 0; }
                    colour = genSequence.at(i++);
                }
                
                Square* temp = theBoard[r][c];
                Basic* basicSq = new Basic;
                setSquareinBoard(r, c, basicSq, colour, lock);
                delete temp;
                
            } // end if
        } // end for
    } // end for
}



// Setters
void Board::levelUpdate(int currLevel){
	level = currLevel;
}



void Board::boardScore(int currScore){
    this->score = currScore;
}



void Board::setGenSequence(string genSeq){
	genSequence = genSeq;
}


// Getter
int Board::getScore(){
    return this->score;
}

/*
int Board::getVertical(){
	return vertical;
}

int Board::getHorizontal(){
	return horizontal;
}
*/


// Setter for Squares in Board
void Board::setSquareinBoard(int r, int c, Square* sq, char colour, char lock){
	theBoard[r][c] = sq;
	theBoard[r][c]->setDisplay(td);
	theBoard[r][c]->setSquares(r,c,colour,lock);
	theBoard[r][c]->setWindow(xw);
	theBoard[r][c]->draw();
}


void Board::lockSquare(int r, int c){
	theBoard[r][c]->lockSquares();
}
