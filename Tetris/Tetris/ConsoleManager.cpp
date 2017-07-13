#include "ConsoleManager.h"

#include "GridSection.h"

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SPOTTED_RECTANGLE	((char)178)
#define FILLED_RECTANGLE	((char)219)
#define FILLED_SQUARE		((char)254)

using namespace std;

vector<string> ConsoleManager::sConsoleLeft;
vector<string> ConsoleManager::sConsoleMiddle;
vector<string> ConsoleManager::sConsoleRight;

int ConsoleManager::sBlockEnum = 0;
char ConsoleManager::sBlockChar = FILLED_RECTANGLE;
bool ConsoleManager::sColorEnabled = true;
bool ConsoleManager::sBlankCharEnabled = false;


void ConsoleManager::InitGame()
{
	// Make each section width sizes that add to the desired width
	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		sConsoleLeft.push_back( string(SCREEN_WIDTH/3, ' ') );
		sConsoleMiddle.push_back( string(SCREEN_WIDTH/3, ' ') );
		sConsoleRight.push_back( string(SCREEN_WIDTH/3, ' ') );
	}
}

void ConsoleManager::PrintNextScreen(bool clear)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Clear screen before printing again
	if (clear)
	{
		system("CLS");
	}

	// Print each section of the console
	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		cout << sConsoleLeft[i];

		for (int j = 0; j < SCREEN_WIDTH/3; ++j)
		{
			OutputCharWithColor(consoleHandle, sConsoleMiddle[i][j]);
		}

		for (int j = 0; j < SCREEN_WIDTH/3; ++j)
		{
			OutputCharWithColor(consoleHandle, sConsoleRight[i][j]);
		}

		cout << endl;
	}
}

void ConsoleManager::SetLine(string line, CONSOLE_SECTION section, int lineNumber)
{
	// Ensure string input is correct length
	while (line.length() < (SCREEN_WIDTH/3))
	{
		line += " ";
	}

	// Determine console to edit
	switch (section)
	{
	case CONSOLE_SECTION::LEFT:
		sConsoleLeft[lineNumber] = line;
		break;
	case CONSOLE_SECTION::MIDDLE:
		sConsoleMiddle[lineNumber] = line;
		break;
	case CONSOLE_SECTION::RIGHT:
		sConsoleRight[lineNumber] = line;
		break;
	}
}

void ConsoleManager::PrintFromFile(string filename)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Open file with given name
	ifstream inputFile;
	inputFile.open(filename);

	// Print contents
	char c;
	while (!inputFile.eof())
	{
		inputFile.get(c);

		// Replace characters and use appropriate colors
		switch (c)
		{
		case 'T':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::RED);
			break;
		case 'E':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::YELLOW);
			break;
		case 't':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::GREEN);
			break;
		case 'R':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::CYAN);
			break;
		case 'I':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::BLUE);
			break;
		case 'S':
			c = FILLED_RECTANGLE;
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::MAGENTA);
			break;
		default:
			SetConsoleTextAttribute(consoleHandle, GRID_SPACE_VALUE::WHITE);
			break;
		}

		cout << c;
	}
	cout << endl << endl;

	inputFile.close();
}

vector<string> ConsoleManager::GetFileStrings(string filename)
{
	vector<string> ret;

	// Open file with given name
	ifstream inputFile;
	inputFile.open(filename);

	// Error handling
	if (!inputFile)
	{
		cout << "ERROR READING FILE" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	// Move file contents into list of strings
	int counter = 0;
	char line[256];

	while (!inputFile.eof())
	{
		inputFile.getline(line, 256);
		ret.push_back(line);
		
		// Replace # symbol with rectangle
		for (unsigned int i = 0; i < ret[counter].length(); ++i)
		{
			if (ret[counter][i] == GRID_SPACE_VALUE::FILLED)
			{
				ret[counter][i] = SPOTTED_RECTANGLE;
			}
		}

		++counter;
	}

	inputFile.close();

	return ret;
}

void ConsoleManager::NextBlockChar()
{
	// Cycle through ASCII values
	sBlockEnum = (sBlockEnum + 1) % 4;

	// Change ASCII character
	switch (sBlockEnum)
	{
	case 0:
		sBlockChar = FILLED_RECTANGLE;
		break;
	case 1:
		sBlockChar = '#';
		break;
	case 2:
		sBlockChar = 'O';
		break;
	case 3:
		sBlockChar = '*';
		break;
	}
}

void ConsoleManager::ToggleColor()
{
	sColorEnabled = !sColorEnabled;

	// When color is turned off, set color to white for everything
	if (!sColorEnabled)
	{
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), GRID_SPACE_VALUE::WHITE );
	}
}

void ConsoleManager::ToggleHelperGrid()
{
	sBlankCharEnabled = !sBlankCharEnabled;
}

void ConsoleManager::OutputCharWithColor(HANDLE& handle, char c)
{
	// Space requires color
	if (GridSection::IsColorValue(c))
	{
		if (sColorEnabled)
		{
			// Change color to output based on value
			SetConsoleTextAttribute(handle, c);
		}

		// Change character to output to current ASCII character
		c = sBlockChar;
	}

	// Space is empty, no color needed
	else if (sColorEnabled)
	{
		SetConsoleTextAttribute(handle, GRID_SPACE_VALUE::WHITE);
	}

	// Do not use empty space symbol when flag not set
	if (c == GRID_SPACE_VALUE::EMPTY && !sBlankCharEnabled)
	{
		c = ' ';
	}

	// Output character
	cout << c;
}
