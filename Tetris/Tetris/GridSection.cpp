#include "GridSection.h"


GridSection::GridSection(int width, int height)
	: mWidth(width), mHeight(height), mGrid(nullptr)
{
	// Create the area
	mGrid = new GRID_SPACE_VALUE*[height];
	for (int i = 0; i < height; ++i)
	{
		mGrid[i] = new GRID_SPACE_VALUE[width];
	}

	// Initialize all values to default
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			mGrid[i][j] = GRID_SPACE_VALUE::EMPTY;
		}
	}
}

GridSection::~GridSection()
{
	if (mGrid != nullptr)
	{
		// Free the allocated memory for the grid
		for (int i = mHeight-1; i >= 0; --i)
		{
			delete[] mGrid[i];
		}
		delete[] mGrid;
		mGrid = nullptr;
	}
}

GridSection::GridSection(GridSection && other)
	: mWidth(other.mWidth), mHeight(other.mHeight), mGrid(other.mGrid)
{
	// Set other to default state
	other.mWidth = 0;
	other.mHeight = 0;
	other.mGrid = nullptr;
}

GridSection& GridSection::operator=(GridSection && other)
{
	// Clean up old grid, if any exists
	if (mGrid != nullptr)
	{
		// Free the allocated memory for the grid
		for (int i = mHeight-1; i >= 0; --i)
		{
			delete[] mGrid[i];
		}
		delete[] mGrid;
	}

	// Copy over values
	mWidth = other.mWidth;
	mHeight = other.mHeight;
	mGrid = other.mGrid;

	// Set other to default state
	other.mWidth = 0;
	other.mHeight = 0;
	other.mGrid = nullptr;

	return *this;
}

GridSection& GridSection::operator=(const GridSection & other)
{
	// Clean up old grid, if any exists
	if (mGrid != nullptr)
	{
		// Free the allocated memory for the grid
		for (int i = mHeight-1; i >= 0; --i)
		{
			delete[] mGrid[i];
		}
		delete[] mGrid;
	}

	// Copy over values
	mWidth = other.mWidth;
	mHeight = other.mHeight;

	// Deep copy grid values
	mGrid = new GRID_SPACE_VALUE*[mHeight];
	for (int i = 0; i < mHeight; ++i)
	{
		mGrid[i] = new GRID_SPACE_VALUE[mWidth];

		for (int j = 0; j < mWidth; ++j)
		{
			mGrid[i][j] = other.mGrid[i][j];
		}
	}

	return *this;
}

GridSection* GridSection::Clone() const
{
	// Create the new object
	GridSection* ret = new GridSection(mWidth, mHeight);

	// Copy grid contents
	for (int i = 0; i < mHeight; ++i)
	{
		for (int j = 0; j < mWidth; ++j)
		{
			(ret->mGrid)[i][j] = mGrid[i][j];
		}
	}

	return ret;
}

void GridSection::ClearGrid()
{
	for (int i = 0; i < mHeight; ++i)
	{
		for (int j = 0; j < mWidth; ++j)
		{
			mGrid[i][j] = GRID_SPACE_VALUE::EMPTY;
		}
	}
}

void GridSection::RemoveValue(GRID_SPACE_VALUE value)
{
	for (int i = 0; i < mHeight; ++i)
	{
		for (int j = 0; j < mWidth; ++j)
		{
			if (mGrid[i][j] == value)
			{
				mGrid[i][j] = GRID_SPACE_VALUE::EMPTY;
			}
		}
	}
}

void GridSection::ReplaceValue(GRID_SPACE_VALUE find, GRID_SPACE_VALUE replace)
{
	for (int i = 0; i < mHeight; ++i)
	{
		for (int j = 0; j < mWidth; ++j)
		{
			if (mGrid[i][j] == find)
			{
				mGrid[i][j] = replace;
			}
		}
	}
}

GRID_SPACE_VALUE GridSection::Get(int row, int col) const
{
	return mGrid[row][col];
}

void GridSection::Set(int row, int col, GRID_SPACE_VALUE value)
{
	mGrid[row][col] = value;
}

std::vector<std::string> GridSection::ShapeStrings() const
{
	std::vector<std::string> ret;

	for (int i = 0; i < mHeight; ++i)
	{
		ret.push_back("");
		for (int j = 0; j < mWidth; ++j)
		{
			switch (mGrid[i][j])
			{
			case GRID_SPACE_VALUE::EMPTY:
				ret[i] += ".";
				break;
			case GRID_SPACE_VALUE::FILLED:
				ret[i] += "#";
				break;
			case GRID_SPACE_VALUE::MARKER:
				ret[i] += "*";
				break;
			case GRID_SPACE_VALUE::RED:
			case GRID_SPACE_VALUE::MAGENTA:
			case GRID_SPACE_VALUE::YELLOW:
			case GRID_SPACE_VALUE::CYAN:
			case GRID_SPACE_VALUE::BLUE:
			case GRID_SPACE_VALUE::SILVER:
			case GRID_SPACE_VALUE::GREEN:
			case GRID_SPACE_VALUE::GRAY:
			case GRID_SPACE_VALUE::WHITE:
				ret[i] += " ";
				ret[i][j] = (char)(mGrid[i][j]);
				break;
			case 0:
				ret[i] += 'Z';
				break;
			default:
				ret[i] += "?";
				break;
			}
		}
	}

	return ret;
}

bool GridSection::IsColorValue(char value)
{
	bool ret = false;

	switch (value)
	{
	case (char)GRID_SPACE_VALUE::RED:
	case (char)GRID_SPACE_VALUE::MAGENTA:
	case (char)GRID_SPACE_VALUE::YELLOW:
	case (char)GRID_SPACE_VALUE::CYAN:
	case (char)GRID_SPACE_VALUE::BLUE:
	case (char)GRID_SPACE_VALUE::SILVER:
	case (char)GRID_SPACE_VALUE::GREEN:
	case (char)GRID_SPACE_VALUE::GRAY:
	case (char)GRID_SPACE_VALUE::WHITE:
		ret = true;
		break;
	}

	return ret;
}
