#pragma once

#include "Piece.h"

#include <vector>


class PieceManager final
{
public:

	// Determines the first two tetromino sequences
	static void InitGame();

	// Gives the piece in storage and moves onto the next piece
	static Piece GetNextPiece(bool removeFromList = true);

	// Replaces the current piece with the one in storage
	static void SwapPiece(Piece & currentPiece);


private:

	// Use randomization to determine next sequence of pieces to give
	static void CreateNextSequence(std::vector<int> & sequence, bool fill = true);


	// The tetromino sequence currently being picked from
	static std::vector<int> sCurrentSequence;

	// The tetromino sequence to be used once the next one finishes
	static std::vector<int> sNextSequence;

	// Used to iterate through current sequence
	static int sSequenceIndex;

	// Used in edge case where backup sequence needs to be remade
	static bool sDirtyNextSequence;
};

