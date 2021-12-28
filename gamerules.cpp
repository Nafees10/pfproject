#include "base.h"
#include "gamerules.h"
#include <iostream>

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

bool move12(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	if (!candyCheck(grid[r1][c1], CandyProperty::Wrapped) ||
		!candyCheck(grid[r2][c2], CandyProperty::Wrapped))
		return false;
	std::cout << "doing 12\n";
	for (int r = r2 - 2; r <= r2 + 2; r ++){
		for (int c = c2 - 2; c <= c2 + 2; c ++){
			bool f = candyCrush(r, c);
			std::cout << "crushed " << r << " " << c << " " << f << "\n";
		}
	}
	return true;
}

bool move11(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	int centerR = -1, centerC = -1;
	if (candyCheck(grid[r1][c1], CandyProperty::Wrapped) &&
		candyCheck(grid[r2][c2], CandyProperty::Striped)){
		centerR = r1;
		centerC = c1;
	}else if (candyCheck(grid[r2][c2], CandyProperty::Wrapped) &&
		candyCheck(grid[r1][c1], CandyProperty::Striped)){
		centerR = r2;
		centerC = c2;
	}
	if (centerR == -1 && centerC == -1)
		return false;
	std::cout << "doing 11\n";
	for (int r = 0; r < ROWS; r ++){
		for (int c = centerC - 1; c <= centerC + 1; c ++){
			candyCrush(r, c);
		}
	}
	for (int c = 0; c < COLS; c ++){
		for (int r = centerR - 1; r <= centerR + 1; r ++){
			candyCrush(r, c);
		}
	}
	return true;
}

bool move10(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	int centerR = -1, centerC = -1;
	if (candyCheck(grid[r1][c1], CandyProperty::Wrapped) &&
		candyCheck(grid[r2][c2], CandyProperty::ColorBomb)){
		centerR = r1;
		centerC = c1;
	}else if (candyCheck(grid[r2][c2], CandyProperty::Wrapped) &&
		candyCheck(grid[r1][c1], CandyProperty::ColorBomb)){
		centerR = r2;
		centerC = c2;
	}
	if (centerR == -1 && centerC == -1)
		return false;
	std::cout << "doing 10\n";
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS;  c++){
			if (r >= centerR - 1 && r <= centerR + 1 &&
				c >= centerC - 1 && c <= centerC + 1)
				candyCrush(r, c);
			else
				grid[r][c] = grid[centerR][centerC];
		}
	}
	return true;
}

bool move9(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	int centerR = -1, centerC = -1;
	if (candyCheck(grid[r1][c1], CandyProperty::Striped) &&
		candyCheck(grid[r2][c2], CandyProperty::ColorBomb)){
		centerR = r1;
		centerC = c1;
	}else if (candyCheck(grid[r2][c2], CandyProperty::Striped) &&
		candyCheck(grid[r1][c1], CandyProperty::ColorBomb)){
		centerR = r2;
		centerC = c2;
	}
	if (centerR == -1 && centerC == -1)
		return false;
	std::cout << "doing 9\n";
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (candyCheck(grid[r][c], candyGetColor(grid[centerR][centerC]))){
				// crush rows and column centered on (r,c)
				for (int y = 0; y < ROWS; y ++)
					candyCrush(y, c);
				for (int x = 0; x < COLS; x ++)
					candyCrush(r, x);
			}
		}
	}
	return true;
}

bool move8(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	if (!candyCheck(grid[r1][c1], CandyProperty::ColorBomb) ||
		!candyCheck(grid[r2][c2], CandyProperty::ColorBomb))
		return false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			candyCrush(r, c);
		}
	}
	return true;
}

bool move7(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	int color = -1;
	if (candyCheck(grid[r1][c1], CandyProperty::ColorBomb) &&
		candyCheck(grid[r2][c2], CandyProperty::Plain))
		color = candyGetColor(grid[r2][c2]);
	else if (candyCheck(grid[r1][c1], CandyProperty::Plain) &&
		candyCheck(grid[r2][c2], CandyProperty::ColorBomb))
		color = candyGetColor(grid[r1][c1]);
	if (color == -1)
		return false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (candyCheck(grid[r][c], color))
			candyCrush(r, c);
		}
	}
	return true;
}
