#include "InputManager.h"

#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cctype>


GAME_INPUT InputManager::GetNext()
{
	GAME_INPUT ret = GAME_INPUT::INVALID;

	// Grab the raw input
	int input = _getch();

	// Convert into enum
	for (int i = 0; i < (int)GAME_INPUT::INVALID; ++i)
	{
		if (InputKeyValue((GAME_INPUT)i) == input)
		{
			ret = (GAME_INPUT)i;
			break;
		}
	}

	return ret;
}

std::string InputManager::InputKeyString(GAME_INPUT input)
{
	std::string ret = "";

	switch (input)
	{
	case GAME_INPUT::QUIT:
		ret = "0";
		break;
	case GAME_INPUT::NEW_GAME:
		ret = "9";
		break;
	case GAME_INPUT::MOVE_LEFT:
		ret = "A";
		break;
	case GAME_INPUT::MOVE_RIGHT:
		ret = "D";
		break;
	case GAME_INPUT::ROTATE_CW:
		ret = "E";
		break;
	case GAME_INPUT::ROTATE_CCW:
		ret = "Q";
		break;
	case GAME_INPUT::SWAP:
		ret = "W";
		break;
	case GAME_INPUT::DROP:
		ret = "S";
		break;
	case GAME_INPUT::CHANGE_BLOCKS:
		ret = "X";
		break;
	case GAME_INPUT::TOGGLE_COLOR:
		ret = "C";
		break;
	case GAME_INPUT::TOGGLE_BLANKS:
		ret = "Z";
		break;
	}

	return ret;
}

char InputManager::InputKeyValue(GAME_INPUT input)
{
	char ret = ' ';

	switch (input)
	{
	case GAME_INPUT::QUIT:
		ret = '0';
		break;
	case GAME_INPUT::NEW_GAME:
		ret = '9';
		break;
	case GAME_INPUT::MOVE_LEFT:
		ret = 'a';
		break;
	case GAME_INPUT::MOVE_RIGHT:
		ret = 'd';
		break;
	case GAME_INPUT::ROTATE_CW:
		ret = 'e';
		break;
	case GAME_INPUT::ROTATE_CCW:
		ret = 'q';
		break;
	case GAME_INPUT::SWAP:
		ret = 'w';
		break;
	case GAME_INPUT::DROP:
		ret = 's';
		break;
	case GAME_INPUT::CHANGE_BLOCKS:
		ret = 'x';
		break;
	case GAME_INPUT::TOGGLE_COLOR:
		ret = 'c';
		break;
	case GAME_INPUT::TOGGLE_BLANKS:
		ret = 'z';
		break;
	}

	return ret;
}
