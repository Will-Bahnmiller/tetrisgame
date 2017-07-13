#include "Piece.h"


Piece::Piece(TETROMINO_SHAPE shape)
	: mShapeType(shape), mShapeGrid(4,4)
{
	GRID_SPACE_VALUE gridValue = GetGridValue();

	// Set blocks based on shape
	switch (shape)
	{
	case TETROMINO_SHAPE::I:
		mShapeGrid.Set(0,0, gridValue);		// #   
		mShapeGrid.Set(1,0, gridValue);		// #   
		mShapeGrid.Set(2,0, gridValue);		// #   
		mShapeGrid.Set(3,0, gridValue);		// #   
		break;
	case TETROMINO_SHAPE::J:
		mShapeGrid.Set(0,1, gridValue);		//  #  
		mShapeGrid.Set(1,1, gridValue);		//  #  
		mShapeGrid.Set(2,0, gridValue);		// ##  
		mShapeGrid.Set(2,1, gridValue);		//     
		break;
	case TETROMINO_SHAPE::L:
		mShapeGrid.Set(0,0, gridValue);		// #   
		mShapeGrid.Set(1,0, gridValue);		// #   
		mShapeGrid.Set(2,0, gridValue);		// ##  
		mShapeGrid.Set(2,1, gridValue);		//     
		break;
	case TETROMINO_SHAPE::O:
		mShapeGrid.Set(0,0, gridValue);		// ##  
		mShapeGrid.Set(0,1, gridValue);		// ##  
		mShapeGrid.Set(1,0, gridValue);		//     
		mShapeGrid.Set(1,1, gridValue);		//     
		break;
	case TETROMINO_SHAPE::S:
		mShapeGrid.Set(0,1, gridValue);		//  ## 
		mShapeGrid.Set(0,2, gridValue);		// ##  
		mShapeGrid.Set(1,0, gridValue);		//     
		mShapeGrid.Set(1,1, gridValue);		//     
		break;
	case TETROMINO_SHAPE::T:
		mShapeGrid.Set(0,0, gridValue);		// ### 
		mShapeGrid.Set(0,1, gridValue);		//  #  
		mShapeGrid.Set(0,2, gridValue);		//     
		mShapeGrid.Set(1,1, gridValue);		//     
		break;
	case TETROMINO_SHAPE::Z:
		mShapeGrid.Set(0,0, gridValue);		// ##  
		mShapeGrid.Set(0,1, gridValue);		//  ## 
		mShapeGrid.Set(1,1, gridValue);		//     
		mShapeGrid.Set(1,2, gridValue);		//     
		break;
	}
}

TETROMINO_SHAPE Piece::GetShape() const
{
	return mShapeType;
}

GRID_SPACE_VALUE Piece::GetGridValue() const
{
	GRID_SPACE_VALUE ret = GRID_SPACE_VALUE::EMPTY;

	switch (mShapeType)
	{
	case TETROMINO_SHAPE::I:
		ret = GRID_SPACE_VALUE::CYAN;
		break;
	case TETROMINO_SHAPE::J:
		ret = GRID_SPACE_VALUE::BLUE;
		break;
	case TETROMINO_SHAPE::L:
		ret = GRID_SPACE_VALUE::SILVER;
		break;
	case TETROMINO_SHAPE::O:
		ret = GRID_SPACE_VALUE::YELLOW;
		break;
	case TETROMINO_SHAPE::S:
		ret = GRID_SPACE_VALUE::GREEN;
		break;
	case TETROMINO_SHAPE::T:
		ret = GRID_SPACE_VALUE::MAGENTA;
		break;
	case TETROMINO_SHAPE::Z:
		ret = GRID_SPACE_VALUE::RED;
		break;
	}

	return ret;
}

std::vector<std::string> Piece::ShapeStrings() const
{
	return mShapeGrid.ShapeStrings();
}

const GridSection & Piece::ShapeGrid() const
{
	return mShapeGrid;
}

bool Piece::TryMovePiece(bool moveLeft)
{
	int direction = (moveLeft) ? -1 : 1;
	int endCondition = (moveLeft) ? 4 : -1;

	// Create copy of grid
	GridSection* gridCopy = mShapeGrid.Clone();

	// Test moving each piece in given direction
	for (int i = 0; i < 4; ++i)
	{
		int j = (moveLeft) ? 0 : 3;
		for (; j != endCondition; j -= direction)
		{
			GRID_SPACE_VALUE value = gridCopy->Get(i, j);

			// Only move occupied spaces
			if (value != GRID_SPACE_VALUE::EMPTY)
			{
				// Do not move outside 4x4 box
				int destination = j + direction;
				if (destination < 0 || destination >= 4)
				{
					delete gridCopy;
					return false;
				}

				// Do not move into another occupied spot
				if (gridCopy->Get(i, destination) != GRID_SPACE_VALUE::EMPTY)
				{
					delete gridCopy;
					return false;
				}

				// Move space over
				gridCopy->Set(i, destination, value);
				gridCopy->Set(i, j, GRID_SPACE_VALUE::EMPTY);
			}
		}
	}

	// Copy new grid over
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mShapeGrid.Set(i, j, gridCopy->Get(i, j));
		}
	}

	// All pieces moved successfully
	delete gridCopy;
	return true;
}

void Piece::RotatePiece(bool clockwise)
{
	// Create copy of grid before editing
	GridSection* gridCopy = mShapeGrid.Clone();

	// Clockwise rotation by 90 degrees
	if (clockwise)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mShapeGrid.Set(i,j, gridCopy->Get(3-j, i));
			}
		}
	}

	// Counter-clockwise rotation by 90 degrees
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mShapeGrid.Set(i,j, gridCopy->Get(j, 3-i));
			}
		}
	}

	// Delete copy when finished
	delete gridCopy;
}
