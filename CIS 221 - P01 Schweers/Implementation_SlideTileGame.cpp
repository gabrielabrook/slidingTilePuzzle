// ******************************************************************************
// Desc: Initialization.cpp file to allow execution in Driver_SlideTileGame.cpp
// ******************************************************************************

// HEADER FILE
#include "Specification_SlideTileGame.h"

// EXTERNAL LIBRARIES/DEPENDENCIES
#include <iostream>
#include <iomanip>
#include <windows.h>

// CONSTANTS
#define PIVOT			0		// used to mark the pivot spot (blank area) on the puzzle
#define PIVOT_SYMBOL	"*"		// used to show the pivot location when drawing the board

#define ROW_DEFAULT		3
#define COL_DEFAULT		3

#define SLIDE_UP		0		// pass to slideTile() to trigger UP movement
#define SLIDE_LEFT		1		// pass to slideTile() to trigger LEFT movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_RIGHT		3		// pass to slideTile() to trigger RIGHT movement
#define EXIT			4

#define UNSET			-1		// used to arbitrarily indicate an undetermined state in a constuct

#define COLOR_DEFAULT	7
#define COLOR_RED		12
#define COLOR_GREEN		10

// CONSTRUCTOR
SlidingPuzzle::SlidingPuzzle() {					// initializing attributes & setting up array
	this->rowSize = ROW_DEFAULT;
	this->columnSize = COL_DEFAULT;
	this->theBoard = new int*[ROW_DEFAULT];			// a new array of size 3 (default, correlates to rowSize value)
	this->solutionBoard = new int*[ROW_DEFAULT];	// a new solution array of size 3 (default, used to check if board is solved)
}

// PARAMETERIZED CONSTRUCTOR (OVERLOAD CONSTRUCTOR)
SlidingPuzzle::SlidingPuzzle(int height, int width) {	// setting up NxM array (2D array)
	this->rowSize = height;
	this->columnSize = width;
	this->theBoard = NULL;
	this->solutionBoard = NULL;
}

// DESTRUCTOR
SlidingPuzzle::~SlidingPuzzle() {						// deallocates memory for NxM board (board and solution board)
	for (int i = 0; i < rowSize; i++) {
		delete[] theBoard[i]; 
		delete[] solutionBoard[i];
	}
	delete[] theBoard; 
	delete[] solutionBoard;
}

// INITIALIZEBOARD() METHOD
void SlidingPuzzle::InitializeBoard(int rowUser, int columnUser) {	// fills 2D array with values and pivot symbol
	// LOCAL VARS
	int counter = 1;												// starts at 1 for visuals
	rowSize = rowUser;
	columnSize = columnUser;
	theBoard = new int*[rowSize];									// creates array via user-inputted rowSize

	for (int i = 0; i < rowSize; i++) {
		theBoard[i] = new int[columnSize];							// creates 2D/double pointer array (NxM) with user inputted columnSize		
	}

	solutionBoard = new int* [rowSize];								// sets unchanged solutionBoard to theBoard, saves solution
	for (int i = 0; i < rowSize; i++) {
		solutionBoard[i] = new int[columnSize];
	}

	// filling theBoard and solutionBoard with good values
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (counter != rowSize * columnSize) {	// if not last spot on board... count from 1 - (rowSize*columnSize)
				theBoard[i][j] = counter;
				solutionBoard[i][j] = counter;
				counter++;
			}
			else {
				theBoard[i][j] = PIVOT;				// mark spot with pivot value
				solutionBoard[i][j] = PIVOT;
			}
		}
	}
}

// PRINTBOARD() METHOD 
void SlidingPuzzle::PrintBoard(int rowUser, int columnUser) {
	// LOCAL VARS
	int counter = 1;
	rowSize = rowUser;
	columnSize = columnUser;

	// FOR COLOR DISPLAY
	HANDLE displayHandle;
	displayHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// PRINTING BOARD
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (theBoard[i][j] == PIVOT) {									// if pivot mark...
				SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);		// default color (grey)
				cout << setw(3) << PIVOT_SYMBOL;							// add * mark on board added
			}
			else {
				
				if (theBoard[i][j] == solutionBoard[i][j]) {				// if correct...
					SetConsoleTextAttribute(displayHandle, COLOR_GREEN);	// make correctly placed numbers green
				}
				else {														// if not solved...
					SetConsoleTextAttribute(displayHandle, COLOR_RED);		// make incorrectly placed numbers red
				}
				cout << setw(3) << theBoard[i][j];							// printing theBoard contents
			}
		}
		cout << endl;
	}
}

// ISBOARDSOLVED() METHOD
bool SlidingPuzzle::isBoardSolved(int rowUser, int columnUser) {
	// LOCAL VARS
	int i, j = 0;
	int counter = 1;
	rowSize = rowUser;
	columnSize = columnUser;

	// FOR COLOR
	HANDLE displayHandle;
	displayHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// CHECKING CONTENTS OF SOLUTION BOARD AGAINST CURRENT BOARD STATE
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < columnSize; j++) {
			if (theBoard[i][j] != solutionBoard[i][j]) {	// if not equal to solution...
				SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);
				cout << "Board State: ";
				SetConsoleTextAttribute(displayHandle, COLOR_RED);
				cout << "UNSOLVED" << endl << endl;
				return false;								// game is not finished
			}
		}
	}

	SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);
	cout << "Board State: ";
	SetConsoleTextAttribute(displayHandle, COLOR_GREEN);
	cout << "SOLVED" << endl << endl;

	return true;											// else set IsBoardSolved() to true
}

// SLIDETILE() METHOD
bool SlidingPuzzle::slideTile(int directionCode, int rowUser, int columnUser) {
	// LOCAL VARS
	int emptyRow = 0;
	int emptyCol = 0;
	rowSize = rowUser;
	columnSize = columnUser;
	bool availableMoves[4] = { true, true, true, true };    // W, A, S, D

	// FINDING THE PIVOT MARK ON THE BOARD
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (theBoard[i][j] == PIVOT) {
				emptyRow = i;
				emptyCol = j;
			}
		}
	}

	// DEFINING VALID, LEGAL MOVES
	if (emptyRow + 1 > rowSize - 1) {	// if any moves result in going over board dimensions (NxM)
		availableMoves[2] = false;		// move is not valid and does not execute.
	}
	else if (emptyRow - 1 < 0) {
		availableMoves[0] = false;
	}
	if (emptyCol - 1 < 0) {
		availableMoves[1] = false;
	}
	else if (emptyCol + 1 > columnSize - 1) {
		availableMoves[3] = false;
	}

	// MOVE SET
	if (availableMoves[directionCode]) { // if avaliableMoves was not set to false above...
		switch (directionCode) {
		case SLIDE_UP:
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow - 1][emptyCol];
			theBoard[emptyRow - 1][emptyCol] = 0;
			emptyRow = emptyRow - 1;
			return true;				// return true when move is successfully made
			break;
		case SLIDE_LEFT:
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow][emptyCol - 1];
			theBoard[emptyRow][emptyCol - 1] = 0;
			emptyCol = emptyCol - 1;
			return true;
			break;
		case SLIDE_DOWN:
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow + 1][emptyCol];
			theBoard[emptyRow + 1][emptyCol] = 0;
			emptyRow = emptyRow + 1;
			return true;
			break;
		case SLIDE_RIGHT:
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow][emptyCol + 1];
			theBoard[emptyRow][emptyCol + 1] = 0;
			emptyCol = emptyCol + 1;
			return true;
			break;
		case EXIT:
			cout << endl << "Thanks for playing!" << endl;
			exit(0);					// EXIT TO OS
		case UNSET:
			cout << "This is not a valid move." << endl;
		}
	}
	
	return false;						// otherwise, return false if moves aren't made above
}

// SCRAMBLEBOARD() METHOD
void SlidingPuzzle::scrambleBoard(int rowUser, int columnUser) {
	// LOCAL VARS
	int slide = 0;
	rowSize = rowUser;
	columnSize = columnUser;

	cout << endl << endl;
	cout << "Scrambling the tiles..." << endl;

	for (int i = 0; i < 10000; i++) {
		slide = rand() % 4;						// gives a number between 0-3 and slides tiles accordingly (4 moves)
		slideTile(slide, rowUser, columnUser); 
	}

	cout << "Scrambling complete, press any key to begin solving." << endl;
}

// PRINTBORDER() METHOD
void SlidingPuzzle::PrintBorder() {
	cout << "*************************************************" << endl
	<< setw(46) << "-+- S L I D I N G  T I L E  P U Z Z L E -+-" << endl
	<< "*************************************************" << endl << endl;
}

// PLAYGAME() METHOD
void SlidingPuzzle::PlayGame(int rowUser, int columnUser) {
	// LOCAL VARS
	char keyStroke = ' ';

	// FOR COLOR
	HANDLE displayHandle;
	displayHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while (!isBoardSolved(rowUser, columnUser)) {				// while board is not solved (game in progress)...
		system("CLS");											// clears screen
		SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);	// sets color back to grey for text below
		PrintBorder();											// prints cosmetic border
		PrintBoard(rowUser, columnUser);						// prints new scrambled board

		isBoardSolved(rowUser, columnUser);						// displays board state to user (solved/unsovled)
		SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);	

		// Asking for user input
		cout << "(W --> UP  |  A --> LEFT  |  S --> DOWN  |  D --> RIGHT) OR E to EXIT" << endl;
		cout << "Which way to slide: ";
		cin >> keyStroke;				// taking user input

		switch (toupper(keyStroke)) {	// toupper allows upper & lowercase input
		case 'W':
			slideTile(SLIDE_UP, rowUser, columnUser);
			break;
		case 'A':
			slideTile(SLIDE_LEFT, rowUser, columnUser);
			break;
		case 'S':
			slideTile(SLIDE_DOWN, rowUser, columnUser);
			break;
		case 'D':
			slideTile(SLIDE_RIGHT, rowUser, columnUser);
			break;
		case 'E':						// user exit tunnel
			slideTile(EXIT, rowUser, columnUser);
			break;
		case UNSET:
			cout << "That direction does not exist." << endl;
		}
	}
}





