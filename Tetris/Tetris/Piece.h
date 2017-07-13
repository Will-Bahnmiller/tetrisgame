#pragma once

#include "GridSection.h"

#include <vector>
#include <string>


// Defines the 4-block shape of the piece
enum TETROMINO_SHAPE
{
	I, J, L, O, S, T, Z, TOTAL
};


class Piece final
{
public:

	// Creates piece based on given shape
	Piece(TETROMINO_SHAPE shape = (TETROMINO_SHAPE)0);

	// Accessor for the shape type
	TETROMINO_SHAPE GetShape() const;

	// Returns the Grid value stored in this piece
	GRID_SPACE_VALUE GetGridValue() const;

	// Computes 4x4 shape as a list of strings
	std::vector<std::string> ShapeStrings() const;

	// Accessor to grid
	const GridSection& ShapeGrid() const;

	// Moves the piece, and returns whether successful or not
	bool TryMovePiece(bool moveLeft);

	// Rotates the piece
	void RotatePiece(bool clockwise);


private:

	// The shape type of this piece
	TETROMINO_SHAPE mShapeType;

	// The actual shape as a 4x4 grid
	GridSection mShapeGrid;
};

