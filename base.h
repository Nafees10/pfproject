#ifndef BASE_H
#define BASE_H

#define ROWS 9
#define COLS 9

enum CandyColor : int{
	Red			= 1 << 0,
	Yellow		= 1 << 1,
	Green		= 1 << 2,
	Blue		= 1 << 3,
	Orange		= 1 << 4,
	ColorBomb	= 1 << 5,
	AllColors	= Red | Yellow | Green | Blue | Orange | ColorBomb,
};

enum CandyProp : int{
	/// plain candy
	Simple		= 1 << 8,
	/// wrapped candy
	Wrapped		= 1 << 9,
	/// stripped candy
	Stripped	= 1 << 10,
	/// will be crushed before updating screen
	Crushed		= 1 << 11,
	AllProps	= Simple | Wrapped | Stripped,
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
/// Returns: true if done, false if invalid row/col
bool candyCrush(int row, int col, bool incrementScore);

/// Returns: a random candy
int candyGetRandom();

/// Returns: number of points for crushing a candy
int candyGetPoints(int candy);

/// Returns: candy's color. Match with CandyColor::X
int candyGetColor(int candy);

/// Returns: candy's properties. Match with CandyProp::X
int candyGetType(int candy);

/// Returns: true if a `candy` is of `color`
///
/// color comes from CandyColor::X
bool candyCheck(int candy, int color);

/// Returns: true if a `candy` is of `color` and of `type`
///
/// color comes from CandyColor::X, type from CandyType::X
bool candyCheck(int candy, int color, int type);

/// checks type of candy.
///
/// Returns: true if matches
bool candyCheckType(int candy, int type);

#endif
