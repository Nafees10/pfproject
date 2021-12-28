#ifndef GAME_RULES_H
#define GAME_RULES_H

/// translates CandyProrperty candy to 0-21 candy number
int translateCandyToInt(int candy);

/// tries move 12
///
/// Returns: true if it did something
bool move12(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);

/// tries move 11
///
/// Returns: true if it did something
bool move11(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);

/// tries move 10
///
/// Returns: true if it did something
bool move10(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);

/// tries move 9
///
/// Returns: true if it did something
bool move9(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);

/// tries move 9
///
/// Returns: true if it did something
bool move9(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);


/// tries move 8
///
/// Returns: true if it did something
bool move8(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);


/// tries move 7
///
/// Returns: true if it did something
bool move7(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);

/// tries move 6
///
/// Returns: true if it did something
bool move6(int grid[ROWS][COLS]);

/// tries move 5
///
/// Returns: true if it did something
bool move5(int grid[ROWS][COLS]);

/// tries move 4
///
/// Returns: true if it did something
bool move4(int grid[ROWS][COLS]);

/// tries move 3
///
/// Returns: true if it did something
bool move3(int grid[ROWS][COLS]);

/// tries move 2
///
/// Returns: true if it did something
bool move2(int grid[ROWS][COLS]);

/// tries move 1
///
/// Returns: true if it did something
bool move1(int grid[ROWS][COLS]);

#endif
