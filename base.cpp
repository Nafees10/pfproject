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
			if (candyCheckType(_grid[r][c], CandyProp::Crushed))
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
	if (row < 0 || col < 0 || row > ROWS || col > COLS)
		return false;
	if (incrementScore)
		_score += candyGetPoints(_grid[row][col]);
	_grid[row][col] |= CandyProp::Crushed;
	return true;
}

int candyGetRandom(){
	int candy = 1 << (rand() % 6); // color
	candy |= 1 << (8 + (rand() % 3)); // property
	return candy;
}

int candyGetPoints(int candy){
	if (candyCheckType(candy, CandyProp::Crushed))
		return 0; // candy already marked as crushed
	switch (candyGetColor(candy)){
		case CandyColor::Red:
		case CandyColor::Yellow:
			return 30;
		case CandyColor::Green:
			return 40;
		case CandyColor::Blue:
			return 50;
		case CandyColor::Orange:
			return 60;
		default:
			return 0;
	}
}

int candyGetColor(int candy){
	return candy & CandyColor::AllColors;
}

int candyGetType(int candy){
	return candy & CandyProp::AllProps;
}

bool candyCheck(int candy, int color){
	return (candy & color) != 0;
}

bool candyCheck(int candy, int color, int type){
	return (candy & color) != 0 && (candy & type) != 0;
}

bool candyCheckType(int candy, int type){
	return (candy & type) != 0;
}
