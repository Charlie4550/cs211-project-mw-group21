#ifndef GAME2048_HELPER_H
#define GAME2048_HELPER_H

const int BOARD_SIZE = 5;

// Moves every row as far left as possible.
// Returns true if the board changed and stores the points earned in scoreGained.
bool move_left(int board[BOARD_SIZE][BOARD_SIZE], int& scoreGained);

bool move_right(int board[BOARD_SIZE][BOARD_SIZE], int& scoreGained);

bool move_up(int board[BOARD_SIZE][BOARD_SIZE], int& scoreGained);

bool move_down(int board[BOARD_SIZE][BOARD_SIZE], int& scoreGained);

bool add_random_tile(int board[BOARD_SIZE][BOARD_SIZE]);

bool check_win(int board[BOARD_SIZE][BOARD_SIZE]);

bool check_game_over(int board[BOARD_SIZE][BOARD_SIZE]);

bool save_game(int board[BOARD_SIZE][BOARD_SIZE], int totalScore);

bool load_game(int board[BOARD_SIZE][BOARD_SIZE], int& totalScore);

#endif
