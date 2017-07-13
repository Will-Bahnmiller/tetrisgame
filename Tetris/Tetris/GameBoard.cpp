#include "GameBoard.h"

#include "GridSection.h"

#include <cstdlib>
#include <vector>
#include <string>

using namespace std;


GameBoard::GameBoard()
	: mBoard(BOARD_WIDTH, BOARD_HEIGHT)
{
}

vector<string> GameBoard::ShapeStrings() const
{
	return mBoard.ShapeStrings();
}

void GameBoard::ClearMarkers()
{
	mBoard.RemoveValue(GRID_SPACE_VALUE::MARKER);
}

void GameBoard::DropPiece(const Piece& piece, const PreparationRow& prepRow, bool actuallyDrop)
{
	// Use the pre-placed markers to avoid recomputing drop location
	if (actuallyDrop)
	{
		mBoard.ReplaceValue(GRID_SPACE_VALUE::MARKER, piece.GetGridValue());
	}

	// Compute the location where the piece would land if dropped
	else
	{
		// Create slightly taller board to place piece above to start
		GridSection tallBoard = GridSection(BOARD_WIDTH, BOARD_HEIGHT+4);

		// Place piece by copying entire preparation row
		vector<string> gridSection = prepRow.ShapeStrings();
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				char value = gridSection[i][j];
				if (value != (char)GRID_SPACE_VALUE::EMPTY)
				{
					tallBoard.Set(i,j, GRID_SPACE_VALUE::MARKER);
				}
			}
		}

		// Place board onto copy
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				tallBoard.Set(i+4, j, mBoard.Get(i,j));
			}
		}

		// Move marker spaces down until one hits something
		int topMostRow = 0;
		bool canMoveDown = true;
		
		while (canMoveDown)
		{
			// Only need to check four rows at a time
			for (int i = 0; (i < 4) && canMoveDown; ++i)
			{
				int currentRow = i + topMostRow;

				if (currentRow < BOARD_HEIGHT+4)
				{
					for (int j = 0; j < BOARD_WIDTH; ++j)
					{
						// Found piece space
						if (tallBoard.Get(currentRow, j) == GRID_SPACE_VALUE::MARKER)
						{
							if (currentRow < BOARD_HEIGHT+3)
							{
								// Check below for a filled space
								int belowValue = tallBoard.Get(currentRow+1, j);

								if (belowValue != GRID_SPACE_VALUE::EMPTY
									&& belowValue != GRID_SPACE_VALUE::MARKER)
								{
									canMoveDown = false;
									break;
								}
							}
							else
							{
								canMoveDown = false;
							}
						}
					}
				}
			}

			// Move all markers down one row
			if (canMoveDown)
			{
				for (int i = 4; i >= 0; --i)
				{
					int currentRow = i + topMostRow;

					if (currentRow < BOARD_HEIGHT+3)
					{
						for (int j = 0; j < BOARD_WIDTH; ++j)
						{
							// Found marker, move it down a row
							if (tallBoard.Get(currentRow, j) == GRID_SPACE_VALUE::MARKER)
							{
								tallBoard.Set(currentRow+1, j, tallBoard.Get(currentRow, j));
								tallBoard.Set(currentRow, j, GRID_SPACE_VALUE::EMPTY);
							}
						}
					}
				}

				++topMostRow;
				if (topMostRow >= BOARD_HEIGHT+3)
				{
					canMoveDown = false;
				}
			}
		}

		// Transfer tall board values to actual board
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				mBoard.Set(i,j, tallBoard.Get(i+4, j));
			}
		}
	}
}

int GameBoard::CheckClearedRows()
{
	int clearedCounter = 0;

	// Check each row, starting from the top
	for (int row = 0; row < BOARD_HEIGHT; ++row)
	{
		// Assume filled until empty space found
		bool isFilled = true;

		// Check each element, going column by column
		for (int col = 0; col < BOARD_WIDTH; ++col)
		{
			// Empty space found means this row is not filled
			if (mBoard.Get(row, col) == GRID_SPACE_VALUE::EMPTY)
			{
				isFilled = false;
				break;
			}
		}

		// Found a row with every element filled
		if (isFilled)
		{
			++clearedCounter;

			// Move rows down one at a time
			for (int i = row-1; i >= 0; --i)
			{
				for (int col = 0; col < BOARD_WIDTH; ++col)
				{
					mBoard.Set(i+1,col, mBoard.Get(i, col));
				}
			}
		}
	}

	return clearedCounter;
}

bool GameBoard::CheckGameOver()
{
	bool gameover = false;

	// Check the top row for a filled space
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		// Found at least one non-empty space
		if (mBoard.Get(0, i) != GRID_SPACE_VALUE::EMPTY)
		{
			gameover = true;
			break;
		}
	}

	// Change all spaces to same color
	if (gameover)
	{
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				if (mBoard.Get(i, j) != GRID_SPACE_VALUE::EMPTY)
				{
					mBoard.Set(i, j, GRID_SPACE_VALUE::GRAY);
				}
			}
		}
	}


	return gameover;
}
