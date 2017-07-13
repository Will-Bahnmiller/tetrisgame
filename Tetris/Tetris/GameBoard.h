#pragma once

#include "GridSection.h"
#include "Piece.h"
#include "PreparationRow.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20


class GameBoard final
{
public:

	// Initializes the empty board
	GameBoard();

	// Computes entire board shape as a list of strings
	std::vector<std::string> ShapeStrings() const;

	// Clears the board of any drop markers
	void ClearMarkers();

	// Drop the given piece onto the board
	void DropPiece(const Piece& piece, const PreparationRow& prepRow, bool actuallyDrop = true);

	// Remove filled rows and move everything else down, returns number of rows that were cleared
	int CheckClearedRows();

	// Checks top row for any filled space
	bool CheckGameOver();


private:

	// The actual board, representing filled and unfilled grid spaces
	GridSection mBoard;

};

