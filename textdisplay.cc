#include <iostream>
//#include <ncurses.h>	// need to compile with -lncurses
#include <cstdlib>
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            basicDisplay[i][j] = "___";
        }
    }
}

void TextDisplay::notify(int r, int c, char lock, char special, char colour){
    basicDisplay[r][c][0] = lock;
    basicDisplay[r][c][1] = special;
    basicDisplay[r][c][2] = colour;
}

ostream &operator<<(ostream &out, const TextDisplay &td){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            out << td.basicDisplay[i][j] << " ";
		//	mvaddstr(i,j,td.basicDisplay[i][j]+" ");
        }
        out << endl;
    }
    return out;
}

/*
bool TextDisplay::curses_started = false;
void TextDisplay::endCurses(){
	if (curses_started && !isendwin()){
		endwin();
	}
}

void TextDisplay::startCurses(){
	if (curses_started) {
		refresh();
	}
	else {
		initscr();
		cbreak();
		noecho();
		intrflush(stdscr, false);
		keypad(stdscr, true);
		atexit(endCurses);
		curses_started = true;
	}
}

void TextDisplay::showCurseDisplay(){
	startCurses();
	for (int r = 0; r < 10; r++){
		for (int c = 0; c < 10; c++){
			mvaddstr(r,c*4,basicDisplay[r][c].c_str());
		}
	}
	refresh();
	getch();
}
*/

/*
int main(){
    TextDisplay neww = TextDisplay();
	
    neww.showCurseDisplay();
    neww.notify(0,2, 'l','v','3');
    neww.showCurseDisplay();
}

*/
