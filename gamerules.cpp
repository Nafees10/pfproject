#include "base.h"
#include "gamerules.h"

/// grid is passed as parameter (grid[ROWS][COLS])
/// ROWS is a literal defined as 9
/// COLS is a literal defined as 9

/// Use function candyCrush(row, col, true) to crush a candy at row, col

/// candyGetColor(int candy) will return the candy color
/// eg:
/// if (candyGetColor(grid[0][0]) == CandyColor::Red){
/// 	cout << "Candy at 0,0 is red"
///}

/// similarly, candyGetType will return its properties
/// eg:
/// if (candyGetCType(grid[0][0]) == CandyProp::Wrapped){
/// 	cout << "Candy at 0,0 is red"
///}

/// or you can use candyCheck to check if color and/or type matches
/// eg:
/// if (candyCheck(grid[0][0], CandyColor::Blue))
/// 	cout << "Candy is blue";
/// if (candyCheck(grid[0][0], CandyColor:::Blue, CandyProp::Stripped))
/// 	cout << "Blue stripped";

/// or candyCheckType will check only type
/// eg:
/// if (candyCheckType(grid[0][0], CandyProp::Simple))
/// 	cout << "Blue stripped";

