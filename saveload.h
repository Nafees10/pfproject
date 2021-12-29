#ifndef SAVELOAD_H
#define SAVELOAD_H

#define SAVE_FILE_NAME "savefile.txt"

bool gameLoad(int grid[ROWS][COLS], int &score,int &scoreTarget,int &movesLeft);

bool gameSave(int grid[ROWS][COLS], int score, int scoreTarget, int movesLeft);

#endif
