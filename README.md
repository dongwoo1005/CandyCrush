Square Swapper 5000
================
Screenshot:
----------------
![alt text](http://dongwoo1005.github.io./image/SquareSwapper.png "SquareSwapper")

Description:
----------------
It's basically Candy Crush Saga.
Check out [UML](http://dongwoo1005.github.io./pdf/uml.pdf) and [Design Document](http://dongwoo1005.github.io./pdf/finalDesignDoc.pdf) for implementation details.

Requirements:
----------------
###X11
- Linux: be sure to pass –Y option if using an ssh connection.
- Windows with Putty: make sure you run an X server such as [XMing](http://sourceforge.net/projects/xming/)
- Mac: install [XQuartz](http://xquartz.macosforge.org/landing/) on a newer Mac OS.

###Compiling:
- g++ example.cc -lX11 (Makefile is written in this way)
<br> or if above doesn’t work on Mac, you need to explicitly tell g++ where X11 is located:
- g++ example.cc -lX11 -L/usr/X11/lib -I/usr/X11/include

Available Commands:
--------------------
`swap x y z`<br>
swaps the square at the (x,y) co-ordinate with the square in the z direction (0 for north, 1 for south, 2 for west and 3 for east) e.g. swap 4 5 3 results in an attempt to swap the square at (4,5) to the square to the east (right) i.e. the square at cell location (4,6).<br>
`hint`<br>
the game returns a valid move (x,y,z as above) that would lead to a match.<br>
`scramble`<br>
Available only if no moves are possible, this command reshuffles the squares on the board (no new cells are created)<br>
`levelup`<br>
Increases the difficulty level of the game by one. You may clear the board and create a new one suitable for that level. If there is no higher level, this command has no effect.<br>
`leveldown`<br>
The same as above, but this time decreasing the difficulty level of the game by one.<br>
`restart`<br>
Clears the board and starts a new game at the same level. The player's score is reset to 0. If you have implemented a high score feature, that score is not reset.<br>

Command line option:
---------------------
- *-text* runs the program in text-only mode. No graphics are displayed. The default behavior (no -text) is to show both text and graphics.
- *-seed xxx* sets the random number generator's seed to xxx. If you don't set the seed, you always get the same random sequence every time you run the program.
- *-scriptfile xxx* uses xxx for this level's initial board configuration. You can assume that the specified file will contain a valid board configuration for that level in the format discussed above. Files may contain a last line indicating a pre-determined order in which coloured BasicSquare should be generated. If a specific sequence is provided this overrides any random generation of squares for that level. If no such sequence is provided, the default behavior for that level should take place. This command line argument is used to ease testing.
- *-startlevel n* starts the game in level n. The game starts in level 0 if this option is not supplied.
- *-testing* runs the game in testing mode. During testing mode, if a match causes a chain reaction, each step of the chain reaction is drawn. After each step is drawn, the program waits for the command next to draw the next step. Alternately, the command continue can be given to run through the remainder steps from the match.