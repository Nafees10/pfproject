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
			candyCrush(r, c);
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
	std::cout << "doing 8\n";
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
	std::cout << "doing 7\n";
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (candyCheck(grid[r][c], color))
			candyCrush(r, c);
		}
	}
	return true;
}

bool move6(int grid[ROWS][COLS]){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			bool wrappedFound = false;
			int i;
			int count;
			for (i = r, count = 0; i < ROWS; i ++){
				if (!candyCheck(grid[i][c], color))
					break;
				wrappedFound = wrappedFound ||
					candyCheck(grid[i][c], CandyProperty::Wrapped);
				count ++;
			}
			if (count >= 3 && wrappedFound){
				ret = true;
				std::cout << "doing 6 with color " << color << "\n";
				for (; i >= r; i --){
					if (candyCheck(grid[i][c], color, CandyProperty::Wrapped))
						candyCrush(i - 1, c - 1, i + 1, c + 1);
				}
			}
			wrappedFound = false;
			for (i = c, count = 0; i < COLS; i ++){
				if (!candyCheck(grid[r][i], color))
					break;
				wrappedFound = wrappedFound ||
					candyCheck(grid[r][i], color, CandyProperty::Wrapped);
				count ++;
			}
			if (count >= 3 && wrappedFound){
				ret = true;
				std::cout << "doing 6 with color " << color << "\n";
				for (; i >= c; i --){
					if (candyCheck(grid[r][i], color, CandyProperty::Wrapped))
						candyCrush(r - 1, i - 1, r + 1, i + 1);
				}
			}
		}
	}
	return ret;
}

bool move5(int grid[ROWS][COLS]){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			bool stripedFound = false;
			int i;
			int count;
			for (i = r, count = 0; i < ROWS; i ++){
				if (!candyCheck(grid[i][c], color))
					break;
				stripedFound = stripedFound ||
					candyCheck(grid[i][c], CandyProperty::Striped);
				count ++;
			}
			if (count >= 3 && stripedFound){
				ret = true;
				std::cout << "doing 5 with color " << color << "\n";
				for (; i >= r; i --){
					if (candyCheck(grid[i][c], color, CandyProperty::HStriped))
						candyCrush(i, 0, i, COLS);
					if (candyCheck(grid[i][c], color, CandyProperty::VStriped))
						candyCrush(0, c, ROWS, c);
				}
			}
			stripedFound = false;
			for (i = c, count = 0; i < COLS; i ++){
				if (!candyCheck(grid[r][i], color))
					break;
				stripedFound = stripedFound ||
					candyCheck(grid[r][i], color, CandyProperty::Striped);
				count ++;
			}
			if (count >= 3 && stripedFound){
				ret = true;
				std::cout << "doing 5 with color " << color << "\n";
				for (; i >= c; i --){
					if (candyCheck(grid[r][i], color, CandyProperty::HStriped))
						candyCrush(i, 0, i, COLS);
					if (candyCheck(grid[r][i], color, CandyProperty::VStriped))
						candyCrush(0, c, ROWS, c);
				}
			}
		}
	}
	return ret;
}

bool move4(int grid[ROWS][COLS]){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			int i;
			int count;
			for (i = r, count = 0; i < ROWS && count < 5; i ++){
				if (!candyCheck(grid[i][c], color))
					break;
				count ++;
			}
			if (count >= 5){
				ret = true;
				candyCrush(r, c, r + count - 1, c);
				grid[r + 2][c] = candyGet(CandyProperty::ColorBomb,
										  CandyProperty::Plain);
			}
			for (i = c, count = 0; i < COLS && count < 5; i ++){
				if (!candyCheck(grid[r][i], color))
					break;
				count ++;
			}
			if (count >= 5){
				ret = true;
				candyCrush(r, c, r, c + count - 1);
				grid[r][c + 2] = candyGet(CandyProperty::ColorBomb,
										  CandyProperty::Plain);
			}
		}
	}
	return ret;
}

bool move3(int grid[ROWS][COLS]){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			bool consecutiveV = true;
			bool consecutiveH = false;
			int r1 = -1;
			int c1 = -1;
			for (int i = r; i < r + 3 && consecutiveV; i ++){
				consecutiveV = candyCheck(grid[i][c], color,
										  CandyProperty::Plain);
				if (consecutiveH)
					continue;
				consecutiveH = true;
				if (c >= 2){
					r1 = i;
					c1 = c - 2;
					for (int j = c - 2; j <= c && consecutiveH; j ++)
						consecutiveH = candyCheck(grid[i][j], color,
										  CandyProperty::Plain);
				}
				if (c < COLS - 2 && !consecutiveH){
					r1 = i;
					c1 = c;
					consecutiveH = true;
					for (int j = c; j <= c + 2 && consecutiveH; j ++)
						consecutiveH = candyCheck(grid[i][j], color,
										  CandyProperty::Plain);
				}
			}
			std::cout << "move 3: V/H: " << consecutiveV << '/' << consecutiveH
				<< "\n";
			if (consecutiveV && consecutiveH){
				ret = true;
				for (int y = r; y < r + 3; y ++)
					candyCrush(y, c);
				for (int x = c1; x < c1 + 3; x ++)
					candyCrush(r1, x);
				grid[r1][c] = candyGet(color, CandyProperty::Wrapped);
				std::cout << "did move 3\n";
			}
		}
	}
	return ret;
}

bool move2(int grid[ROWS][COLS], int r1, int c1, int r2, int c2){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			int i;
			int count;
			for (i = r, count = 0; i < ROWS && count < 4; i ++){
				if (!candyCheck(grid[i][c], color, CandyProperty::Plain))
					break;
				count ++;
			}
			if (count >= 4){
				ret = true;
				std::cout << "doing 2\n";
				candyCrush(r, c, r + count - 1, c);
				grid[r + 2][c] = candyGet(color, CandyProperty::VStriped);
			}
			for (i = c, count = 0; i < COLS && count < 4; i ++){
				if (!candyCheck(grid[r][i], color, CandyProperty::Plain))
					break;
				count ++;
			}
			if (count >= 4){
				ret = true;
				std::cout << "doing 2\n";
				candyCrush(r, c, r, c + count - 1);
				if (r1 == r && c2 >= c && c2 < c + 4){
					std::cout << "c2\n";
					grid[r][c2] = candyGet(color, CandyProperty::HStriped);
				}else if (r2 == r && c1 >= c && c1 < c + 4){
					std::cout << "c1\n";
					grid[r][c1] = candyGet(color, CandyProperty::HStriped);
				}else
					grid[r][c + 2] = candyGet(color, CandyProperty::HStriped);
			}
		}
	}
	return ret;
}

bool move1(int grid[ROWS][COLS]){
	bool ret = false;
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int color = candyGetColor(grid[r][c]);
			int i;
			int count;
			for (i = r, count = 0; i < ROWS && count < 3; i ++){
				if (!candyCheck(grid[i][c], color))
					break;
				count ++;
			}
			if (count >= 3){
				ret = true;
				candyCrush(r, c, r + count - 1, c);
			}
			for (i = c, count = 0; i < COLS && count < 3; i ++){
				if (!candyCheck(grid[r][i], color))
					break;
				count ++;
			}
			if (count >= 3){
				ret = true;
				candyCrush(r, c, r, c + count - 1);
			}
		}
	}
	return ret;
}
