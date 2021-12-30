#include "base.h"
#include <iostream>

void DEBUG_printCandy(int candy){
	switch (candyGetColor(candy)){
		case CandyProperty::Red:
			std::cout << "R";break;
		case CandyProperty::Yellow:
			std::cout << "Y";break;
		case CandyProperty::Green:
			std::cout << "G";break;
		case CandyProperty::Blue:
			std::cout << "B";break;
		case CandyProperty::Orange:
			std::cout << "O";break;
		case CandyProperty::ColorBomb:
			std::cout << "C";break;
	}
	switch (candyGetType(candy)){
		case CandyProperty::Plain:
			std::cout << "P";break;
		case CandyProperty::Wrapped:
			std::cout << "W";break;
		case CandyProperty::HStriped:
			std::cout << "H";break;
		case CandyProperty::VStriped:
			std::cout << "V";break;
		case CandyProperty::ColorBomb:
			std::cout << "B";break;
	}
}

void DEBUG_printGrid(int grid[ROWS][COLS]){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (grid[r][c] == 0)
				std::cout << "  ";
			else
				DEBUG_printCandy(grid[r][c]);
			std::cout << " ";
		}
		std::cout << "\n";
		for (int r = 0; r < ROWS; r ++)
			std::cout << ' ';
		std::cout << '\n';
	}
}
