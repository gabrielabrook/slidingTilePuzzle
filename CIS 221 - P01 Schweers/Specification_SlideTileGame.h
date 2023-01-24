// ********************************************************************
// Desc: Specification.h file to support Driver_SlideTileGame.cpp and
//		 Implementation_SlideTileGame.cpp
// ********************************************************************

#ifndef _SLIDINGTILEGAME_
#define _SLIDINGTILEGAME_

// EXTERNAL LIBRARIES AND DEPENDENCES
#include <iostream>

using namespace std;

// CLASS SLIDING TILE GAME
class SlidingPuzzle {
private:
	// ATTRIBUTES
	int rowSize;			 // for setting the # of rows
	int columnSize;			 // for setting the # of columns
	int **theBoard;			 // for the 2D array (double pointer)
	int **solutionBoard;	 // to hold solution for isBoardSolved() and color output

public:
	// CONSTRUCTOR
	SlidingPuzzle();		 // constructor for initializing and creating space for array (using rowSize)
	SlidingPuzzle(int, int); // creating space for NxM array (rowSize*columnSize), overlaod constructor
	
	// DESTRUCTOR
	~SlidingPuzzle();		 // deallocates memory from theBoard and solutionBoard

	// METHODS
	void InitializeBoard(int, int);	// fills 2D array with values and pivot mark
	void PrintBoard(int, int);		// prints said board with values and pivot symbol
	void scrambleBoard(int, int);	// scrambles the board to allow many board instances to solve
	bool isBoardSolved(int, int);	// checks current board state against solution board
	bool slideTile(int, int, int);	// performs user-inputted sliding moves on board
	void PrintBorder();				// prints a cosmetic border when called
	void PlayGame(int, int);		// starts the game, asks for user input, etc; game mechs.
};
#endif
