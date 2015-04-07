#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <string>
#include <iostream>


class TextDisplay{
	std::string basicDisplay[10][10];
//	static bool curses_started;
//	static void endCurses();
//	void startCurses();
public:
    TextDisplay();
	void notify(int r, int c, char lock, char special, char colour);
	friend std::ostream& operator<<(std::ostream &out, const TextDisplay &td);
	
//	void showCurseDisplay();    
};

#endif
