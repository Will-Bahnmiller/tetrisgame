#pragma once

#include <string>
#include <vector>
#include <windows.h>

// Defines the desired screen dimensions
#define SCREEN_WIDTH	(90)
#define SCREEN_HEIGHT	(29)


// Defines individual sections of the console
enum CONSOLE_SECTION
{
	LEFT, MIDDLE, RIGHT
};


class ConsoleManager final
{
public:

	// Called before games starts to initialize vectors
	static void InitGame();

	// Clears console if specified and then prints output
	static void PrintNextScreen(bool clear = true);

	// Sends string to given line number (0 based) for outputting
	static void SetLine(std::string line, CONSOLE_SECTION section, int lineNumber);

	// Prints out entire file contents to console
	static void PrintFromFile(std::string filename);

	// Returns file contents into a list of strings
	static std::vector<std::string> GetFileStrings(std::string filename);

	// Cycles to the next ASCII character for blocks
	static void NextBlockChar();

	// Toggles color for blocks
	static void ToggleColor();

	// Toggles using '.' symbol for empty spaces
	static void ToggleHelperGrid();


private:

	// Helper method to output characters in color to the console
	static void OutputCharWithColor(HANDLE& handle, char c);


	// Output string lists for each third of the console
	static std::vector<std::string> sConsoleLeft, sConsoleMiddle, sConsoleRight;

	// Used to determine which ASCII value to use for occupied block spaces
	static int sBlockEnum;
	static char sBlockChar;

	// Flag for coloring occupied block spaces
	static bool sColorEnabled;

	// Flag for enabling '.' symbol for empty spaces
	static bool sBlankCharEnabled;
};

