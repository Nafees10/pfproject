#ifndef BASE_H
#define BASE_H

#define ROWS 9
#define COLS 9

#define MIN_TARGET 5000
#define MAX_TARGET 10000

#define MIN_MOVES 20
#define MAX_MOVES 30

/// Candy properties (color + wrapped/...)
enum CandyProperty : int{
	/// Red
	Red			= 1 << 0, // 1
	/// Yellow
	Yellow		= 1 << 1, // 2
	/// Green
	Green		= 1 << 2, // 4
	/// Blue
	Blue		= 1 << 3, // 8
	/// Orange
	Orange		= 1 << 4, // 16
	/// Color Bomb
	ColorBomb	= 1 << 5, // 32
	/// DO NOT USE THIS. ONLY FOR UNDER THE HOOD WORKING
	AllColors	= Red | Yellow | Green | Blue | Orange | ColorBomb,
	/// Plain candy
	Plain		= 1 << 6,
	/// Wrapped candy
	Wrapped		= 1 << 7,
	/// Striped
	Striped		= 1 << 10,
	/// Horizontal Striped
	HStriped	= (1 << 8) | Striped,
	/// Vertical Striped
	VStriped	= (1 << 9) | Striped,
	/// Crushed candy
	Crushed		= 1 << 11,
	/// All properties (Plan + Wrapped + Striped + Crushed)
	/// ONLY FOR UNDER THE HOOD WORKING, DO NOT USE CandyProperty::AllProps
	AllProps	= Plain | Wrapped | HStriped | VStriped | Crushed,
};

/// initializes level, call this to initialize this module
void init();

/// initializes grid to empty
void gridInit();

/// Returns: if there are empty cells in grid
bool gridHasEmpty();

/// candies fall down 1 cell maximum if there is space
///
/// Returns: true if there are empty cells after shifting
void gridStep();

/// Updates textures of candy objects in grid
void gridUpdateTextures();

/// crushes the candy at a cell
///
/// Returns: true if done, false if invalid row/col or already marked as crushed
bool candyCrush(int row, int col);

/// Crushes the candies in rectangle r1,c1 r2,c2 (inclusive)
void candyCrush(int r1, int c1, int r2, int c2);

/// Returns: a random plain candy
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
///
/// coordinates of last swap are optional, but for accurate move#2, needed
bool gridTryCrush(int r1=-1, int c1=-1, int r2=-1, int c2=-1);

/// Swaps two cells, and tries to match if there is any
///
/// Returns: true if swap happened, false if not possible
bool swap(int r1, int c1, int r2, int c2);

/// loads textures, and prepares objects
void initObjects();

/// Draws the score, target, and moves
void drawScore();

/// Draws candies (the grid)
void drawGrid();

void run();

#endif
