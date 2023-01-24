// ************************************************************************
// Name: Gabriela Schweers
// Date: 10/21/2022 - 10/27/2022
// Desc: A sliding tile puzzle game that allows user inputted dimensions
//		 ultilizing object-orientated programming.
// ************************************************************************

// EXTERNAL LIBRARIES AND DEPENDENCIES
#pragma warning(disable:4996)
#include "Specification_SlideTileGame.h"	// including header file
#include <conio.h>							// for _getch()
#include <windows.h>						// for color
#include <iomanip>							// for setw()

// CONSTANTS
#define SLIDE_UP		0		// pass to slideTile() to trigger UP movement
#define SLIDE_LEFT		1		// pass to slideTile() to trigger LEFT movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_RIGHT		3		// pass to slideTile() to trigger RIGHT movement

#define DEFAULT_ROW		3
#define DEFAULT_COL		3

#define COLOR_DEFAULT	7		 
#define COLOR_RED		12
#define COLOR_GREEN		10

#define UNSET			-1		// used to arbitrarily indicate an undetermined state in a constuct

// MAIN
int main() {
	// VARIABLES
	int rowUser = DEFAULT_ROW;
	int columnUser = DEFAULT_COL;

	// SEEDING PSEUDO RANDOM NUMBER GENERATOR
	srand((unsigned int)time(NULL));

	// INSTANTIATE THE CLASS
	SlidingPuzzle someSlidingPuzzle;

	// REQUESTING USER TO INPUT ROW VALUE
	cout << "Welcome to my Sliding Tile Puzzle game! To start, please set your desired board dimensions [MIN 3 - MAX 10]." << endl;
	cout << "- Number of rows desired: ";
	cin >> rowUser;
	
	// ERROR HANDLING PT. 1
	while (cin.fail() == true || (rowUser > 10 || rowUser < 3) || (rowUser != int(rowUser))) {
		cout << "That was not a value within the MIN and MAX board dimensions. Please try again..." << endl;
		cin.clear();		// clear out cin flags
		rewind(stdin);		// purge keyboard buffer

		// re-prompt
		cout << "- Number of rows desired: ";
		cin >> rowUser;
	}

	// REQUESTING USER TO INPUT COLUMN VALUE
	cout << "- Number of columns desired: ";
	cin >> columnUser;

	// ERROR HANDLING PT. 2
	while (cin.fail() == true || (columnUser > 10 || columnUser < 3)) {
		cout << "That was not a value within the MIN and MAX board dimensions. Please try again..." << endl;
		cin.clear();
		rewind(stdin);		

		// re-prompt
		cout << "- Number of columns desired: ";
		cin >> columnUser;
	}

	cout << endl;

	// DISPLAYING INFO TO USER
	someSlidingPuzzle.InitializeBoard(rowUser, columnUser); // initializing playing board
	someSlidingPuzzle.PrintBorder();						// printing cosmetic border
	someSlidingPuzzle.PrintBoard(rowUser, columnUser);		// printing playing board

	HANDLE displayHandle;
	displayHandle = GetStdHandle(STD_OUTPUT_HANDLE);		// prepping color usage 

	SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);	// sets color back to grey

	someSlidingPuzzle.isBoardSolved(rowUser, columnUser);	// displaying board state to user

	SetConsoleTextAttribute(displayHandle, COLOR_DEFAULT);	// sets color back to grey

	cout << "Press any key to begin...";
	_getch();												// induces a pause before continuing...

	someSlidingPuzzle.scrambleBoard(rowUser, columnUser);  // scrambles board before continuing...

	_getch();												// pause...

	// CALLING GAMEPLAY METHOD
	someSlidingPuzzle.PlayGame(rowUser, columnUser);

	// EXIT TO OS
	_getch();
	return 0;
}