#ifndef BASE_H
#define BASE_H

#define ROWS 9
#define COLS 9

#define MIN_TARGET 1000
#define MAX_TARGET 10000

#define MIN_MOVES 20
#define MAX_MOVES 30

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
	/// Striped
	Striped		= 1 << 9,
	/// Horizontal Striped
	HStriped	= (1 << 7) | Striped,
	/// Vertical Striped
	VStriped	= (1 << 8) | Striped,
	/// Crushed candy
	Crushed		= 1 << 10,
	/// All properties (Plan + Wrapped + Striped + Crushed)
	/// ONLY FOR UNDER THE HOOD WORKING, DO NOT USE CandyProperty::AllProps
	AllProps	= Plain | Wrapped | HStriped | VStriped | Crushed,
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
bool candyCrush(int row, int col);

/// Returns: a random candy
int candyGetRandom();

/// Returns: candy whose color is `color` and has a CandyProperty
int candyGet(int color, int property);

/// Returns: number of points for crushing a candy
int candyGetPoints(int candy);

/// Returns: candy's color. Match with CandyProperty::X
int candyGetColor(int candy);

/// Returns: canhdy's properties. Match with CandyProperty::X
int candyGetType(int candy);

/// Returns: true if a `candy` is of a type.
/// type is told by CandyProperty::X
bool candyCheck(int candy, int type1);

/// Returns: true if a `candy` is of type1 and type2
/// types are told by CandyProperty::X
bool candyCheck(int candy, int type1, int type2);

/// Returns: true if a swap can happen
bool swapIsPossible(int r1, int c1, int r2, int c2);

/// Tries to crush all candies that can be crushed
void gridTryCrush();

/// Swaps two cells, and tries to match if there is any
///
/// Returns: true if swap happened, false if not possible
bool swap(int r1, int c1, int r2, int c2);

void run();

#endif
