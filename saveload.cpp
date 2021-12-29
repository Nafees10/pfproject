#include <fstream>
#include "base.h"

bool gameLoad(int grid[ROWS][COLS],int &score,int &scoreTarget,int &movesLeft) {
	std::ifstream fin("file.txt");
	if (!fin)
		return false;
	fin >> score;
	fin >> scoreTarget;
	fin >> movesLeft;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			if (fin.eof())
				return false;
			fin >> grid[r][c];
		}
	}
	return true;
}

bool gameSave(int grid[ROWS][COLS], int score, int scoreTarget, int movesLeft) {
	std::ofstream fout("file.txt");
	if (!fout)
		return false;
	fout << score << std::endl;
	fout << scoreTarget << std::endl;
	fout << movesLeft << std::endl;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++)
			fout << grid[r][c]<<" ";
		fout << std::endl;
	}
	return true;
}
