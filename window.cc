#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height, int version): width(width), height(height) {
	if (version != 0){
		this->version = version;
	}
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
	char color_vals[10][10];
  	char default_colour[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};
	char extra_colour[10][10] = {"white", "black", "coral", "turquoise", "plum", "khaki", "gold", "magenta", "orange", "gray"};

	if (version == 0){
		for (int i=0; i<10; i++){
			strcpy (color_vals[i], default_colour[i]);
		}
	} else {
		for (int i=0; i<10; i++){
			strcpy (color_vals[i], extra_colour[i]);
		}
	}

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);
  usleep(2500);
  XSelectInput(d,w,ExposureMask);
  XFlush(d);
  XEvent event;
  XNextEvent(d,&event); //Hang until the window is ready.
  XSelectInput(d,w,0);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);

}


void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);


  //set default font
  Font f = XLoadFont(d, "6x13");


  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * fStruct = XLoadQueryFont(d, name.str().c_str());

  if (fStruct) { //font was found, replace default
    f = fStruct->fid;
  }


  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
//  ti.font = f->fid;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void Xwindow::drawAccessory(int x, int y, int level, int score, int moves, int movescount, int colour){
    string str = "SQUARESWAPPER 5000";
    string str2 = "BY DONGWOO WILL SON";
    string str3 = " & HAEJUNG CHOI" ;
    stringstream ss;
    stringstream ss2;
    stringstream ss3;
    stringstream ss4;
    
    string s_level="";
    ss << level;
    ss >> s_level;
    string level_string = "    Level: " + s_level;
    
    string s_score="";
    ss2 << score;
    ss2 >> s_score;
    string score_string = "    Score: " + s_score;

    string s_moves="";
    moves = moves -movescount;
    ss4 << moves;
    ss4 >> s_moves;
	if (level < 3) {
		s_moves = "Unlimited";
	}
    string moves_string = "    Moves: " + s_moves;
   /* string s_highscore;
    ss3 << highscore;
    ss3 >> s_highscore;
    string highscore_string = "Highscore: " + s_highscore;*/
    
    XSetForeground(d, gc, colours[White]);
    XFillRectangle(d, w, gc, x, 0, 300, 600);

    drawString(x, y+100, str, colour);
    drawString(x, y+130, str2, colour);
    drawString(x, y+160, str3, colour);
    drawString(x, y+190, level_string, colour);
    drawString (x, y+220, score_string , colour);
    drawString(x, y+250, moves_string, colour);

}

void Xwindow::fillSquares(int x, int y, int width, int height, bool lockFlag, int special, int colour){
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Orange]);
    
    if (special == 0){ //basic
        fillRectangle(x, y, width, height, colour);
    }else if (special == 1){ //lateral
        XFillRectangle(d, w, gc, x , y + (height/2.5)*1.5, width, 5);
        XFillRectangle(d, w, gc, x, y + (height/5.5)*1.5, width, 5);
    }else if (special == 2){ //upright
        XFillRectangle(d, w, gc, x + (width/4) *3, y, 5, height );
        XFillRectangle(d, w, gc, x + (width/4), y, 5, height );
    }else if (special == 3){ //unstable
        int length = 15;
        XFillRectangle(d, w, gc, x + width/6+9, y +height/6+2, length,length);
        XFillRectangle(d, w, gc, x + width/6+9, y +height/6+19, length,length);

    }else if (special == 4){ //psychedelic
        int length = 6;
        XFillRectangle(d, w, gc, x + width/3 - 3, y + height/3 - 3, length, length);
        XFillRectangle(d, w, gc, x + 2*width/3 -3 , y + 2*height/3-3, length, length);
        XFillRectangle(d, w, gc, x + width/2-3, y + height/2 - 3, length, length);
    }
    if (lockFlag){
        XDrawLine(d, w, gc, x, y , x + width, y+height);
        XDrawLine(d, w, gc, x, y+height, x + width, y);
    }
    
}

void Xwindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}
