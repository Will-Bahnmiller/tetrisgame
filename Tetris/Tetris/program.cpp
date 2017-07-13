/// Will Bahnmiller | 2017 | :p

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "GridSection.h"
#include "GameBoard.h"
#include "Piece.h"
#include "PreparationRow.h"
#include "PieceManager.h"
#include "InputManager.h"
#include "ConsoleManager.h"

using namespace std;

int main()
{
	/***** TITLE *****/

	// Print title screen
	ConsoleManager::PrintFromFile("../Tetris/title.txt");

	// Wait for user to begin game
	system("pause");


	/***** SETUP *****/

	// Initialize managers
	InputManager::InitGame();
	PieceManager::InitGame();
	ConsoleManager::InitGame();

	// Initialize game variables
	bool game = true;
	bool gameover = false;

	int linesCleared = 0;
	int blocksPlaced = 0;

	vector<string> gridSection;

	GameBoard gameBoard;
	Piece currentPiece = PieceManager::GetNextPiece();
	PreparationRow prepRow;
	prepRow.SetCurrentPiece(&currentPiece);
	prepRow.ClearAndPlace();

	// Create horizontal boarder for board
	string boarder = string(BOARD_WIDTH, '-');

	// Prepare all texts that won't ever change, before game starts
	ConsoleManager::SetLine("CONTROLS:", CONSOLE_SECTION::LEFT, 5);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::MOVE_LEFT) + "] Move left", CONSOLE_SECTION::LEFT, 6);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::MOVE_RIGHT) + "] Move right", CONSOLE_SECTION::LEFT, 7);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::ROTATE_CW) + "] Rotate CW", CONSOLE_SECTION::LEFT, 8);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::ROTATE_CCW) + "] Rotate CCW", CONSOLE_SECTION::LEFT, 9);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::SWAP) + "] Swap", CONSOLE_SECTION::LEFT, 10);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::DROP) + "] Drop", CONSOLE_SECTION::LEFT, 11);

	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::TOGGLE_COLOR) + "] Toggle color", CONSOLE_SECTION::LEFT, 14);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::TOGGLE_BLANKS) + "] Toggle helper grid", CONSOLE_SECTION::LEFT, 15);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::CHANGE_BLOCKS) + "] Change appearance", CONSOLE_SECTION::LEFT, 16);

	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::NEW_GAME) + "] New game", CONSOLE_SECTION::LEFT, 18);
	ConsoleManager::SetLine("[" + InputManager::InputKeyString(GAME_INPUT::QUIT) + "] Quit", CONSOLE_SECTION::LEFT, 19);

	ConsoleManager::SetLine("     *" + boarder + "*", CONSOLE_SECTION::MIDDLE, 0);
	ConsoleManager::SetLine("     *" + boarder + "*", CONSOLE_SECTION::MIDDLE, 5);
	ConsoleManager::SetLine("     *" + boarder + "*", CONSOLE_SECTION::MIDDLE, BOARD_HEIGHT+6);

	ConsoleManager::SetLine("NEXT:", CONSOLE_SECTION::RIGHT, 0);
	ConsoleManager::SetLine("*----*", CONSOLE_SECTION::RIGHT, 1);
	ConsoleManager::SetLine("*----*", CONSOLE_SECTION::RIGHT, 6);

	/***** GAME *****/

	// Main game loop
	while (game)
	{

		/***** PRINTING *****/

		// Output stats
		ConsoleManager::SetLine("Lines cleared = " + to_string(linesCleared), CONSOLE_SECTION::LEFT, 1);
		ConsoleManager::SetLine("Blocks placed = " + to_string(blocksPlaced), CONSOLE_SECTION::LEFT, 2);

		// Output next piece
		Piece nextPiece = PieceManager::GetNextPiece(false);
		gridSection = nextPiece.ShapeStrings();

		ConsoleManager::SetLine("|" + gridSection[0] + "|", CONSOLE_SECTION::RIGHT, 2);
		ConsoleManager::SetLine("|" + gridSection[1] + "|", CONSOLE_SECTION::RIGHT, 3);
		ConsoleManager::SetLine("|" + gridSection[2] + "|", CONSOLE_SECTION::RIGHT, 4);
		ConsoleManager::SetLine("|" + gridSection[3] + "|", CONSOLE_SECTION::RIGHT, 5);

		// Output preparation row or gameover text
		if (!gameover)
		{
			gridSection = prepRow.ShapeStrings();
		}
		else
		{
			gridSection = ConsoleManager::GetFileStrings("../Tetris/gameover.txt");
		}
		ConsoleManager::SetLine("     |" + gridSection[0] + "|", CONSOLE_SECTION::MIDDLE, 1);
		ConsoleManager::SetLine("     |" + gridSection[1] + "|", CONSOLE_SECTION::MIDDLE, 2);
		ConsoleManager::SetLine("     |" + gridSection[2] + "|", CONSOLE_SECTION::MIDDLE, 3);
		ConsoleManager::SetLine("     |" + gridSection[3] + "|", CONSOLE_SECTION::MIDDLE, 4);

		// Clear board of drop markers
		gameBoard.ClearMarkers();

		// Compute where the piece would land if it dropped
		if (!gameover)
		{
			gameBoard.DropPiece(currentPiece, prepRow, false);
		}

		// Output entire game board
		gridSection = gameBoard.ShapeStrings();

		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			ConsoleManager::SetLine("     |" + gridSection[i] + "|", CONSOLE_SECTION::MIDDLE, i+6);
		}

		// Now that all outputs are done, actually print to console
		ConsoleManager::PrintNextScreen();


		/***** INPUT *****/

		if (!gameover)
		{
			bool validInput = false;

			// Don't bother going through another loop until valid input is given
			while (!validInput)
			{
				// Get user input and perform action
				GAME_INPUT input = InputManager::GetNext();

				switch (input)
				{
				// Quit the game by ending the game loop
				case GAME_INPUT::QUIT:
					game = false;
					validInput = true;
					break;

				// Start a new game by resetting variables
				case GAME_INPUT::NEW_GAME:
					InputManager::InitGame();
					PieceManager::InitGame();
					ConsoleManager::InitGame();
					linesCleared = 0;
					blocksPlaced = 0;
					gameBoard = GameBoard();
					currentPiece = PieceManager::GetNextPiece();
					prepRow = PreparationRow();
					prepRow.SetCurrentPiece(&currentPiece);
					prepRow.ClearAndPlace();
					validInput = true;
					break;

				// Move the current piece left, if possible
				case GAME_INPUT::MOVE_LEFT:
					prepRow.MoveCurrentPiece(true);
					validInput = true;
					break;

				// Move the current piece right, if possible
				case GAME_INPUT::MOVE_RIGHT:
					prepRow.MoveCurrentPiece(false);
					validInput = true;
					break;

				// Rotate current piece clockwise 90 degrees
				case GAME_INPUT::ROTATE_CW:
					prepRow.RotateCurrentPiece(true);
					validInput = true;
					break;

				// Rotate current piece counter-clockwise 90 degrees
				case GAME_INPUT::ROTATE_CCW:
					prepRow.RotateCurrentPiece(false);
					validInput = true;
					break;

				// Swap current piece with the one in storage
				case GAME_INPUT::SWAP:
					PieceManager::SwapPiece(currentPiece);
					prepRow.ClearAndPlace();
					validInput = true;
					break;

				// Drop current piece down into the board, get next piece, check for board changes and gameover
				case GAME_INPUT::DROP:
					gameBoard.DropPiece(currentPiece, prepRow, true);
					linesCleared += gameBoard.CheckClearedRows();
					currentPiece = PieceManager::GetNextPiece();
					prepRow.ClearAndPlace();
					gameover = gameBoard.CheckGameOver();
					++blocksPlaced;
					validInput = true;
					break;

				// Change block ASCII value
				case GAME_INPUT::CHANGE_BLOCKS:
					ConsoleManager::NextBlockChar();
					validInput = true;
					break;

				// Toggle color on/off
				case GAME_INPUT::TOGGLE_COLOR:
					ConsoleManager::ToggleColor();
					validInput = true;
					break;

				// Toggle helper grid on/off
				case GAME_INPUT::TOGGLE_BLANKS:
					ConsoleManager::ToggleHelperGrid();
					validInput = true;
					break;
				}
			}
		}

		// Gameover, wait for quit or new game
		else
		{
			/*system("pause");
			game = false;*/

			bool validInput = false;

			while (!validInput)
			{
				GAME_INPUT input = InputManager::GetNext();

				switch (input)
				{
				case GAME_INPUT::QUIT:
					game = false;
					validInput = true;
					break;

				case GAME_INPUT::NEW_GAME:
					InputManager::InitGame();
					PieceManager::InitGame();
					ConsoleManager::InitGame();
					linesCleared = 0;
					blocksPlaced = 0;
					gameBoard = GameBoard();
					currentPiece = PieceManager::GetNextPiece();
					prepRow = PreparationRow();
					prepRow.SetCurrentPiece(&currentPiece);
					prepRow.ClearAndPlace();
					gameover = false;
					validInput = true;
					break;
				}
			}
		}

	} // end of game loop

	return 0;
}