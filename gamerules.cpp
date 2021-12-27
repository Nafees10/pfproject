#include "base.h"
#include "gamerules.h"

/// grid is passed as parameter (grid[ROWS][COLS])
/// ROWS is a literal defined as 9
/// COLS is a literal defined as 9

/// Use function candyCrush(row, col, true) to crush a candy at row, col

/// candyGetColor(int candy) will return the candy color
/// eg:
/// if (candyGetColor(grid[0][0]) == CandyProperty::Red)
/// 	cout << "Candy at 0,0 is red"

/// similarly, candyGetType will return its properties
/// eg:
/// if (candyGetType(grid[0][0]) == CandyProperty::Wrapped)
/// 	cout << "Candy at 0,0 is Wrapped"

/// or you can use candyCheck to check if color and/or type matches
/// eg:
/// if (candyCheck(grid[0][0], CandyProperty::Blue))
/// 	cout << "Candy is blue";
/// if (candyCheck(grid[0][0], CandyProperty::Plain))
/// 	cout << "Candy is plain";
/// if (candyCheck(grid[0][0], CandyProperty:::Blue, CandyProperty::Stripped))
/// 	cout << "Blue and striped";

/// To create a candy of a color and a type (Plain/Wrapped/Stripped)
/// use candyGet(color, type);
/// int candy = candyGet(CandyProperty::ColorBomb, 0);

/// function prototype for all rules will be:
/// bool name(int[ROWS][COLS] grid, int r1, int c1, int r2, int c2)
/// the function will return true if it did some chnages to grid, false if not
/// r1, c1 and r2, c2 are the candies that were swapped
