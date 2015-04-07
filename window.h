#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
	
class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
	int width, height, version;

public:
	Xwindow(int width=500, int height=500, int version = 0);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.

	// Available Colour
	enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, Turquoise, Coral, Plum, Khaki, Gold};

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	// Draws a string
	void drawString(int x, int y, std::string msg, int colour=Black);

	// Draws a string
	void drawBigString(int x, int y, std::string msg, int colour=Black);

	// Prints the first 10000 available fonts
	void showAvailableFonts();

	// Implementation to draw Squares
	void drawAccessory(int x, int y, int level, int score, int moves, int movescount, int colour);
	void fillSquares(int x, int y, int width, int height, bool lockFlag, int special, int colour);
};

#endif
