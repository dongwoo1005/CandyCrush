/*-------------------------------------------------------------------------------------------
  							 The Game of SquareSwapper5000


@ Description
A match-three style puzzle game that draws elements from popular games, such as Candy 
Crush Saga and the Bejewelled series.

Features:
10 x 10 basic Board
4 Kinds of special Squares: 
	- Lateral, Upright, Unstable and Psychedelic
4 Kinds of Matches: 
	- Horizontal 4 match, Vertical 4 match, L match, and 5 match
	- Accordingly producing Lateral, Upright, Unstable and Psychedelic squares upon match
Graphical Display (using X11) and Text Display
3 Different Levels

Available Commands
swap x y z	 	Swaps the square at (x,y) with the square in the z direction.
				- 0 for North, 1 for South, 2 for West, 3 for East.
hint 			Hints for a valid swap move that would lead to a match.
scramble 		Reshuffles the square on the board (only available when no moves are possible).
levelup			Increases the difficulty level of the game by one.
leveldown 		Decreases the difficulty level of the game by one.
restart			Clears the board and starts a new game at the same level. score is reset to 0.
help			Shows the description for the commands

Command-line Options for Developers:
-text			Runs the program in text-only mode.
-seed xxx		Sets the random number generator's seed to xxx.
-scriptfile xxx Uses xxx for the level's initial board configuration.
-startlevel n	Starts the game in level n
-testing		Runs the game in testing mode.


@ Author: Dongwoo Son & Haejung Choi 
@ Updated: April 3, 2015
@ Version: 1.0
@ Requirement: Make sure you have the necessary libraries to compile graphics for X11.
-------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <cstdlib> // atoi
#include <cstring> // strcmp
#include "squareswapper.h"

using namespace std;

int main(int argc, char* argv[]){


	// Set default variables for command line options
	bool text, testing, bonus = false;
	int seedn = 777;
	int startleveln = 0;
	string filename = "";


	// Set array for the commands and command line option
	const int numOption = 6;
	const char* optionList[numOption] = {"-text", "-seed", "-scriptfile", "-startlevel", "-testing", "-bonus"};
	const int numCommand = 7;	
	string commandList[numCommand] = {"swap", "hint", "scramble", "levelup", "leveldown", "restart","help"};


	// Take command line options
	for (int i = 1; i < argc; ++i){
		if (strcmp(argv[i], optionList[0]) == 0){		// -text
			text = true;
		}
		else if (strcmp(argv[i], optionList[1]) == 0){ 	// -seed
			seedn = atoi(argv[i+1]);
		}
		else if (strcmp(argv[i], optionList[2]) == 0){ 	// -scriptfile
			filename = argv[i+1];
		}
		else if (strcmp(argv[i], optionList[3]) == 0){ 	// -startlevel
			startleveln = atoi(argv[i+1]);
		}
		else if (strcmp(argv[i], optionList[4]) == 0){ 	// -testing
			testing = true;
		} 
		else if (strcmp(argv[i], optionList[5]) == 0){  // -bonus
			bonus = true;
		}
	} // end for


	// Initiate the Board according to the command line options	
	SquareSwapper *theGame = new SquareSwapper;							// Creates the game
	theGame->init(startleveln, seedn, text, testing, filename, bonus);	// initiate according to the options
	theGame->removeMatches();											// Remove existing matches
	cout << *theGame;													// Print the board


    
	// Take commands from cin
	while (1){
		string command;
		cin >> command;


		// EOF terminates the game
		if (cin.eof()){
			delete theGame;
			cout << "GAME OVER" << endl;
			break;
		} // end if



		// Command swap x y z
		if (command == commandList[0]){
			int x, y, z;		
			cin >> x >> y >> z;

			theGame->swap(x,y,z);							// Initial swapping
			bool foundMatch = false;
			bool checkxy = false;
			bool checkxytoz = false;
            if (z == 0 && x != 0){							// if z=North and x isn't first row
				checkxy = theGame->check(x, y);
				checkxytoz = theGame->check(x - 1, y);
				foundMatch = checkxy || checkxytoz;			// check Matches and crush
				if (!foundMatch){
					theGame->swap(x - 1, y, 1);				// swap it back if no match is found
				} // end if
				else {
					theGame->moveCountUp();
				}
            } // end if

            else if (z == 1 && x != 9){ 					// if z=South and x isn't last row
				checkxy = theGame->check(x, y);
				checkxytoz = theGame->check(x + 1, y);
				foundMatch = checkxy || checkxytoz;			// check Matches and crush
				if (!foundMatch){
					theGame->swap(x + 1, y, 0);				// swap it back if no match is found
				} // end if
				else {
					theGame->moveCountUp();
				}
            } // end else if

            else if (z == 2 && y != 0){						// if z=West and y isn't first col
				checkxy = theGame->check(x, y);
				checkxytoz = theGame->check(x, y - 1);
				foundMatch = checkxy || checkxytoz;			// check Matches and crush
				if (!foundMatch){
					theGame->swap(x, y - 1, 3);				// swap it back if no match is found
				} // end if
				else {
					theGame->moveCountUp();
				}
			} // end else if

            else if (z == 3 && y != 9){						// if z=East and y isn't last col
				checkxy = theGame->check(x, y);
				checkxytoz = theGame->check(x, y + 1);
				foundMatch = checkxy || checkxytoz;			// check Matches and crush
				if (!foundMatch){
					theGame->swap(x, y + 1, 2);				// swap it back if no match is found
				} // end if
				else{
					theGame->moveCountUp();
				}
			} // end else if

			else {
				cerr << "Invalid swap" << endl;				// swap is invalid otherwise	
			} // end else

			if (foundMatch){								// When a match is found
				if (testing) { theGame->test(); }			// print board after match and crush
				theGame->dropSquares();						// drop the squares to fill crushed square
				if (testing) { theGame->test(); }			// print board after drop	
				theGame->chainMatches();					// Enter into chain reaction phase

				if (theGame->isLvComplete()){				// check if level completion requirement is met
					cout << "LEVEL COMPLETE!" << endl;
					theGame->levelup();						// if true, level goes up
					theGame->removeMatches();				// and remove initial matches
				} // end if
			} // end if

			cout << *theGame;								// prints the final board after swap

			if (testing) { theGame->turnTestON(); }			// Turn on the test mode back on, 
															// just in case continue command turned it off
		} // end if



		// Command hint
		else if (command == commandList[1]){
			theGame->hint(true);
		} // end else if



		// Command scramble
		else if (command == commandList[2]){ 
			if (!theGame->hint(false)) {	 				// Available only if no moves are possible
				theGame->scramble();						// scramble the board
				theGame->removeMatches();					// remove matched squares
			} // end if 
			else {
				cerr << "Moves are still available." << endl;
			} // end else
			cout << *theGame;								// print the board
		} // end else if



		// Command levelup
		else if (command == commandList[3]){
			theGame->levelup();
			theGame->removeMatches();						// levelup and remove the matched squares
			cout << *theGame;
		} // end else if



		// Command leveldown
		else if (command == commandList[4]){
			theGame->leveldown();
			theGame->removeMatches();						// leveldown and remove the matched squares
			cout << *theGame;
		} // end else if



		// Command restart
		else if (command == commandList[5]){ 
			theGame->restart();				
			theGame->removeMatches();						// restart the game and remove the matched squares
			cout << *theGame;
		} // end else if



		// Command help
		else if (command == commandList[6]){
			cout << "Valid Commands:" << endl;
			cout << "swap x y z; hint; scramble; levelup; leveldown; restart" << endl;
			cout << "Numbers for direction:" << endl;
			cout << "0: North" << endl;
			cout << "1: South" << endl;
			cout << "2: West" << endl;
			cout << "3: East" << endl;
		} // end else if
	} // end while
	

} // end main
