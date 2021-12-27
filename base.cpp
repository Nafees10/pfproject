#include "base.h"
#include <stdlib.h>

/// grid of candies
int _grid[ROWS][COLS];
/// score
int _score;

void init(){
	_score = 0;
	gridInit();
}

void gridInit(){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++)
			_grid[r][c] = 0;
	}
}

bool gridHasEmpty(){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (_grid[r][c] == 0)
				return true;
		}
	}
	return false;
}

void gridStep(){
	// replace crushed with 0
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (candyCheck(_grid[r][c], CandyProperty::Crushed))
				_grid[r][c] = 0;
		}
	}
	for (int c = 0; c < COLS; c ++){
		int shift = 0, r = ROWS - 1;
		while (r - shift >= 0){
			if (_grid[r - shift][c] == 0){
				shift ++;
			}else{
				_grid[r][c] = _grid[r - shift][c];
				r --;
			}
		}
		for (; r >= 0; r --)
			_grid[r][c] = 0;
	}
}

bool candyCrush(int row, int col, bool incrementScore){
	if (row < 0 || col < 0 || row > ROWS || col > COLS ||
		!candyCheck(_grid[row][col], CandyProperty::Crushed))
		return false;
	if (incrementScore)
		_score += candyGetPoints(_grid[row][col]);
	_grid[row][col] |= CandyProperty::Crushed;
	return true;
}

int candyGetRandom(){
	int candy = 1 << (rand() % 6); // color
	candy |= 1 << (8 + (rand() % 3)); // property
	return candy;
}

int candyGet(int color, int property){
	return (color & CandyProperty::ColorBomb) |
		(property & CandyProperty::AllProps);
}

int candyGetPoints(int candy){
	if (candyCheck(candy, CandyProperty::Crushed))
		return 0; // candy already marked as crushed
	switch (candyGetColor(candy)){
		case CandyProperty::Red:
		case CandyProperty::Yellow:
			return 30;
		case CandyProperty::Green:
			return 40;
		case CandyProperty::Blue:
			return 50;
		case CandyProperty::Orange:
			return 60;
		default:
			return 0;
	}
}

int candyGetColor(int candy){
	return candy & CandyProperty::ColorBomb;
}

int candyGetType(int candy){
	return candy & CandyProperty::AllProps;
}

bool candyCheck(int candy, int type){
	return (candy & type) != 0;
}

bool candyCheck(int candy, int type1, int type2){
	return (candy & type1) != 0 && (candy & type2) != 0;
}

bool swapIsPossible(int r1, int c1, int r2, int c2){
	if (r1 == r2)
		return abs(c1 - c2) == 1;
	if (c1 == c2)
		return abs(r1 - r2) == 1;
	return false;
}

bool swap(int r1, int c1, int r2, int c2){
	if (!swapIsPossible(r1, c1, r2, c2))
		return false;
	int tempCandy = _grid[r1][c1];
	_grid[r1][c1] = _grid[r2][c2];
	_grid[r2][c2] = tempCandy;
	// try all move functions

	return true;
}
