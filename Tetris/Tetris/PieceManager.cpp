#include "PieceManager.h"

#include <cstdlib>
#include <time.h>
#include <algorithm>

std::vector<int> PieceManager::sCurrentSequence;
std::vector<int> PieceManager::sNextSequence;
int PieceManager::sSequenceIndex = 0;
bool PieceManager::sDirtyNextSequence = false;


void PieceManager::InitGame()
{
	// Initialize random seed
	srand( (unsigned int)time(NULL) );

	// Create randomized sequences
	CreateNextSequence(sCurrentSequence);
	CreateNextSequence(sNextSequence);
}

Piece PieceManager::GetNextPiece(bool removeFromList)
{
	// Get type from current list
	int pieceType = sCurrentSequence[sSequenceIndex];
	Piece nextPiece = Piece((TETROMINO_SHAPE)pieceType);

	// Move onto next piece
	if (removeFromList)
	{
		++sSequenceIndex;

		// When list is finished, use next one
		if (sSequenceIndex >= TETROMINO_SHAPE::TOTAL)
		{
			// Copy reserved list into current
			sCurrentSequence = sNextSequence;

			// Create new randomized sequence
			CreateNextSequence(sNextSequence, sDirtyNextSequence);
			sDirtyNextSequence = false;

			// Reset index to start of new sequence
			sSequenceIndex = 0;
		}
	}

	return nextPiece;
}

void PieceManager::SwapPiece(Piece & currentPiece)
{
	// Determine current and next shape types
	TETROMINO_SHAPE currentShape = currentPiece.GetShape();
	TETROMINO_SHAPE nextShape;

	// Swap next from current list
	if (sSequenceIndex < TETROMINO_SHAPE::TOTAL)
	{
		nextShape = (TETROMINO_SHAPE)(sCurrentSequence[sSequenceIndex]);
		sCurrentSequence[sSequenceIndex] = (int)(currentShape);
	}

	// Swap next from next list
	else
	{
		nextShape = (TETROMINO_SHAPE)(sNextSequence[0]);
		sNextSequence[0] = (int)(currentShape);
		sDirtyNextSequence = true;
	}

	// Create new piece based on next shape type
	currentPiece = Piece(nextShape);
}

void PieceManager::CreateNextSequence(std::vector<int> & sequence, bool fill)
{
	// Ensure list starts with one of each type of piece
	if (fill)
	{
		sequence = std::vector<int>();
		for (int i = 0; i < TETROMINO_SHAPE::TOTAL; ++i)
		{
			sequence.push_back(i);
		}
	}

	// Rearrange the order
	std::random_shuffle(sequence.begin(), sequence.end());
}
