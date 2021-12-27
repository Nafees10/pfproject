#ifndef BASE_H
#define BASE_H

#define ROWS 9
#define COLS 9

/// Candy properties (color + wrapped/...)
enum CandyProperty : int{
	/// Red
	Red			= 1 << 0,
	/// Yellow
	Yellow		= 1 << 1,
	/// Green
	Green		= 1 << 2,
	/// Blue
	Blue		= 1 << 3,
	/// Orange
	Orange		= 1 << 4,
	/// Color Bomb (i.e: all colors)
	ColorBomb	= Red | Yellow | Green | Blue | Orange,
	/// Plain candy
	Plain		= 1 << 5,
	/// Wrapped candy
	Wrapped		= 1 << 6,
	/// Stripped candy
	Stripped	= 1 << 7,
	/// Horizontal Stripped
	HStripped	= (1 << 8) | Stripped,
	/// Vertical Stripped
	VStripped	= (1 << 9) | Stripped,
	/// Crushed candy
	Crushed		= 1 << 10,
	/// All properties (Plan + Wrapped + Stripped + Crushed)
	/// ONLY FOR UNDER THE HOOD WORKING, DO NOT USE CandyProperty::AllProps
	AllProps	= Plain | Wrapped | Stripped | Crushed,
};

/// initializes level
void init();

/// initializes grid to empty
void gridInit();

/// Returns: if there are empty cells in grid
bool gridHasEmpty();

/// candies fall down 1 cell maximum if there is space
void gridStep();

/// crushes the candy at a cell
///
/// Returns: true if done, false if invalid row/col or already marked as crushed
bool candyCrush(int row, int col, bool incrementScore);

/// Returns: a random candy
int candyGetRandom();

/// Returns: candy whose color is `color` and has a CandyProperty
int candyGet();

/// Returns: number of points for crushing a candy
int candyGetPoints(int candy);

/// Returns: candy's color. Match with CandyProperty::X
int candyGetColor(int candy);

/// Returns: candy's properties. Match with CandyProperty::X
int candyGetType(int candy);

/// Returns: true if a `candy` is of a type.
/// type is told by CandyProperty::X
bool candyCheck(int candy, int type1);

/// Returns: true if a `candy` is of type1 and type2
/// types are told by CandyProperty::X
bool candyCheck(int candy, int type1, int type2);

/// Returns: true if a swap can happen
bool swapIsPossible(int r1, int c1, int r2, int c2);

/// Swaps two cells, and tries to match if there is any
///
/// Returns: true if swap happened, false if not possible
bool swwp(int r1, int c1, int r2, int c2);

#endif
