#include "PreparationRow.h"

#include "GameBoard.h"


PreparationRow::PreparationRow()
	: mGrid(BOARD_WIDTH, 4), mColumnOffset(0), mCurrentPiece(nullptr)
{
}

void PreparationRow::SetCurrentPiece(Piece* newPiece)
{
	mCurrentPiece = newPiece;
}

void PreparationRow::ClearAndPlace()
{
	// Clear current grid contents
	ClearGrid();

	// Place piece onto this grid
	const GridSection& pieceGrid = mCurrentPiece->ShapeGrid();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mGrid.Set(i, (j+mColumnOffset), pieceGrid.Get(i, j));
		}
	}
}

void PreparationRow::MoveCurrentPiece(bool moveLeft)
{
	// Move entire piece over if it cannot move itself
	if (mCurrentPiece->TryMovePiece(moveLeft) == false)
	{
		int direction = (moveLeft) ? -1 : 1;
		int destination = mColumnOffset + direction;

		// Only shift if it remains within board's width
		if (destination >= 0 && destination <= BOARD_WIDTH-4)
		{
			mColumnOffset = destination;

			ClearAndPlace();
		}
	}
	else
	{
		ClearAndPlace();
	}
}

void PreparationRow::RotateCurrentPiece(bool clockwise)
{
	// Rotate the piece
	mCurrentPiece->RotatePiece(clockwise);

	// Update grid
	ClearAndPlace();
}

std::vector<std::string> PreparationRow::ShapeStrings() const
{
	return mGrid.ShapeStrings();
}

int PreparationRow::GetOffset() const
{
	return mColumnOffset;
}

void PreparationRow::ClearGrid()
{
	mGrid.ClearGrid();
}

