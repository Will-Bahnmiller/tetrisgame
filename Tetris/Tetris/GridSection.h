#pragma once

#include <vector>
#include <string>


// Defines the value stored in the 2D int array for the grid
enum GRID_SPACE_VALUE
{
	EMPTY = '.',
	FILLED = '#',
	MARKER = '*',

	RED = 12,
	MAGENTA = 13,
	YELLOW = 14,
	CYAN = 11,
	BLUE = 9,
	SILVER = 7,
	GREEN = 10,
	GRAY = 8,
	WHITE = 15
};


class GridSection final
{
public:

	// Initializes the grid space using given dimensions
	GridSection(int width, int height);
	
	// Deallocates memory
	~GridSection();

	// Move constructor, shallow-copies pointer to allocated grid
	GridSection(GridSection&& other);

	// Move assignment operator, shallow-copies pointer to allocated grid after cleaning up old grid
	GridSection& operator=(GridSection&& other);

	// Assignment operator, deep copies allocated grid after cleaning up old grid
	GridSection& operator=(const GridSection& other);

	// Returns a pointer to an allocated GridSection with the same grid contents and dimensions as this one
	GridSection* Clone() const;

	// Clears out all of the elements of the grid
	void ClearGrid();

	// Searches grid and clears spaces with the given value
	void RemoveValue(GRID_SPACE_VALUE value);

	// Searches grid and replaces spaces with the given value
	void ReplaceValue(GRID_SPACE_VALUE find, GRID_SPACE_VALUE replace);

	// Accessor and setter for grid elements
	GRID_SPACE_VALUE Get(int row, int col) const;
	void Set(int row, int col, GRID_SPACE_VALUE value);

	// Computes contents as a list of strings
	std::vector<std::string> ShapeStrings() const;

	// Determines if given value is a color or not
	static bool IsColorValue(char value);


private:

	// The actual grid
	GRID_SPACE_VALUE** mGrid;

	// Grid dimensions
	int mWidth, mHeight;
};

