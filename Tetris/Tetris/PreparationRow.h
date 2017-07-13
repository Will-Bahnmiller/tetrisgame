#pragma once

#include "GridSection.h"
#include "Piece.h"


class PreparationRow
{

public:

	// Initializes the empty section
	PreparationRow();

	// Sets reference to new current piece
	void SetCurrentPiece(Piece* newPiece);

	// Clears the row and places the piece onto it
	void ClearAndPlace();

	// Moves the piece, if possible
	void MoveCurrentPiece(bool moveLeft);

	// Rotates the piece
	void RotateCurrentPiece(bool clockwise);

	// Computes rectangular shape as a list of strings
	std::vector<std::string> ShapeStrings() const;

	// Returns the offset from the left-most column of the current piece
	int GetOffset() const;


private:

	// Clears out the grid
	void ClearGrid();


	// The actual grid space
	GridSection mGrid;

	// Reference to the current piece
	Piece* mCurrentPiece;

	// Offset from left-most column
	int mColumnOffset;

};

