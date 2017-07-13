#pragma once

#include <string>


// Defines keyboard input for the game
enum GAME_INPUT
{
	QUIT,			// Exits the application
	NEW_GAME,		// Clears everything to start a new game

	MOVE_LEFT,		// Move current piece left one space
	MOVE_RIGHT,		// Move current piece right one space

	ROTATE_CW,		// Rotate current piece clock-wise 90 degrees
	ROTATE_CCW,		// Rotate current piece counter-clockwise 90 degrees

	SWAP,			// Trade current piece for the piece on standby
	DROP,			// Drop current piece down at current location

	CHANGE_BLOCKS,	// Cycles through ASCII characters for the blocks
	TOGGLE_COLOR,	// Turns color on/off
	TOGGLE_BLANKS,	// Toggles using a '.' symbol for empty spaces

	INVALID
};

class InputManager
{
public:

	// (Does nothing)
	static void InitGame() {}

	// Returns the next user input
	static GAME_INPUT GetNext();

	// Translates input enum into human-readable string
	static std::string InputKeyString(GAME_INPUT input);

	// Translates input enum into char value
	static char InputKeyValue(GAME_INPUT input);
};

