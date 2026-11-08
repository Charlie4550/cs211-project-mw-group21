#include "2048_helper.h"
#include <cstdlib>
#include <fstream>

using namespace std;

void process_row_left(int row[BOARD_SIZE], int& scoreGained)
{
    int compacted[BOARD_SIZE] = {0, 0, 0, 0, 0};
    int nextPosition = 0;

    // Move nonzero numbers together.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (row[i] != 0)
        {
            compacted[nextPosition] = row[i];
            nextPosition++;
        }
    }

    // Merge matching neighbors once.
    for (int i = 0; i < BOARD_SIZE - 1; i++)
    {
        if (compacted[i] != 0 &&
            compacted[i] == compacted[i + 1])
        {
            compacted[i] *= 2;
            scoreGained += compacted[i];
            compacted[i + 1] = 0;
            i++;
        }
    }

    // Close gaps created by merging.
    int finalRow[BOARD_SIZE] = {0, 0, 0, 0, 0};
    nextPosition = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (compacted[i] != 0)
        {
            finalRow[nextPosition] = compacted[i];
            nextPosition++;
        }
    }

    // Copy the finished row back.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        row[i] = finalRow[i];
    }
}

bool move_left(int board[BOARD_SIZE][BOARD_SIZE],
               int& scoreGained)
{
    scoreGained = 0;
    bool boardChanged = false;

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        int originalRow[BOARD_SIZE];

        for (int c = 0; c < BOARD_SIZE; c++)
        {
            originalRow[c] = board[r][c];
        }

        process_row_left(board[r], scoreGained);

        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] != originalRow[c])
            {
                boardChanged = true;
            }
        }
    }

    return boardChanged;
}

void process_row_right(int row[BOARD_SIZE], int& scoreGained)
{
    int compacted[BOARD_SIZE] = {0, 0, 0, 0, 0};
    int nextPosition = BOARD_SIZE - 1;

    // Move nonzero numbers to the right.
    for (int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        if (row[i] != 0)
        {
            compacted[nextPosition] = row[i];
            nextPosition--;
        }
    }

    // Merge matching neighbors once, from right to left.
    for (int i = BOARD_SIZE - 1; i > 0; i--)
    {
        if (compacted[i] != 0 &&
            compacted[i] == compacted[i - 1])
        {
            compacted[i] *= 2;
            scoreGained += compacted[i];
            compacted[i - 1] = 0;
            i--;
        }
    }

    // Close gaps created by merging.
    int finalRow[BOARD_SIZE] = {0, 0, 0, 0, 0};
    nextPosition = BOARD_SIZE - 1;

    for (int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        if (compacted[i] != 0)
        {
            finalRow[nextPosition] = compacted[i];
            nextPosition--;
        }
    }

    // Copy the finished row back.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        row[i] = finalRow[i];
    }
}

bool move_right(int board[BOARD_SIZE][BOARD_SIZE],
                int& scoreGained)
{
    scoreGained = 0;
    bool boardChanged = false;

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        int originalRow[BOARD_SIZE];

        // Save the original row.
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            originalRow[c] = board[r][c];
        }

        process_row_right(board[r], scoreGained);

        // Check whether the row changed.
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] != originalRow[c])
            {
                boardChanged = true;
            }
        }
    }

    return boardChanged;
}

void process_column_up(int board[BOARD_SIZE][BOARD_SIZE],
                       int column, int& scoreGained)
{
    int compacted[BOARD_SIZE] = {0, 0, 0, 0, 0};
    int nextPosition = 0;

    // Move nonzero numbers toward the top.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][column] != 0)
        {
            compacted[nextPosition] = board[i][column];
            nextPosition++;
        }
    }

    // Merge matching neighbors once.
    for (int i = 0; i < BOARD_SIZE - 1; i++)
    {
        if (compacted[i] != 0 &&
            compacted[i] == compacted[i + 1])
        {
            compacted[i] *= 2;
            scoreGained += compacted[i];
            compacted[i + 1] = 0;
            i++;
        }
    }

    // Close gaps created by merging.
    int finalColumn[BOARD_SIZE] = {0, 0, 0, 0, 0};
    nextPosition = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (compacted[i] != 0)
        {
            finalColumn[nextPosition] = compacted[i];
            nextPosition++;
        }
    }

    // Copy the finished column back.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[i][column] = finalColumn[i];
    }
}

bool move_up(int board[BOARD_SIZE][BOARD_SIZE],
             int& scoreGained)
{
    scoreGained = 0;
    bool boardChanged = false;

    for (int c = 0; c < BOARD_SIZE; c++)
    {
        int originalColumn[BOARD_SIZE];

        // Save the original column.
        for (int r = 0; r < BOARD_SIZE; r++)
        {
            originalColumn[r] = board[r][c];
        }

        process_column_up(board, c, scoreGained);

        // Check whether the column changed.
        for (int r = 0; r < BOARD_SIZE; r++)
        {
            if (board[r][c] != originalColumn[r])
            {
                boardChanged = true;
            }
        }
    }

    return boardChanged;
}

void process_column_down(int board[BOARD_SIZE][BOARD_SIZE],
                         int column, int& scoreGained)
{
    int compacted[BOARD_SIZE] = {0, 0, 0, 0, 0};
    int nextPosition = BOARD_SIZE - 1;

    // Move nonzero numbers toward the bottom.
    for (int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        if (board[i][column] != 0)
        {
            compacted[nextPosition] = board[i][column];
            nextPosition--;
        }
    }

    // Merge matching neighbors once.
    for (int i = BOARD_SIZE - 1; i > 0; i--)
    {
        if (compacted[i] != 0 &&
            compacted[i] == compacted[i - 1])
        {
            compacted[i] *= 2;
            scoreGained += compacted[i];
            compacted[i - 1] = 0;
            i--;
        }
    }

    // Close gaps created by merging.
    int finalColumn[BOARD_SIZE] = {0, 0, 0, 0, 0};
    nextPosition = BOARD_SIZE - 1;

    for (int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        if (compacted[i] != 0)
        {
            finalColumn[nextPosition] = compacted[i];
            nextPosition--;
        }
    }

    // Copy the finished column back.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[i][column] = finalColumn[i];
    }
}

bool move_down(int board[BOARD_SIZE][BOARD_SIZE],
               int& scoreGained)
{
    scoreGained = 0;
    bool boardChanged = false;

    for (int c = 0; c < BOARD_SIZE; c++)
    {
        int originalColumn[BOARD_SIZE];

        // Save the original column.
        for (int r = 0; r < BOARD_SIZE; r++)
        {
            originalColumn[r] = board[r][c];
        }

        process_column_down(board, c, scoreGained);

        // Check whether the column changed.
        for (int r = 0; r < BOARD_SIZE; r++)
        {
            if (board[r][c] != originalColumn[r])
            {
                boardChanged = true;
            }
        }
    }

    return boardChanged;
}

bool add_random_tile(int board[BOARD_SIZE][BOARD_SIZE])
{
    int emptyCount = 0;

    // Count all empty spaces.
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] == 0)
            {
                emptyCount++;
            }
        }
    }

    // No empty spaces available.
    if (emptyCount == 0)
    {
        return false;
    }

    // Select a random empty space.
    int randomPosition = rand() % emptyCount;

    // Find that empty space and place a 2.
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] == 0)
            {
                if (randomPosition == 0)
                {
                    board[r][c] = 2;
                    return true;
                }

                randomPosition--;
            }
        }
    }

    return false;
}
bool check_win(int board[BOARD_SIZE][BOARD_SIZE])
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] >= 2048)
            {
                return true;
            }
        }
    }

    return false;
}

bool check_game_over(int board[BOARD_SIZE][BOARD_SIZE])
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            // An empty space means the game is not over.
            if (board[r][c] == 0)
            {
                return false;
            }

            // Check the tile to the right.
            if (c < BOARD_SIZE - 1 &&
                board[r][c] == board[r][c + 1])
            {
                return false;
            }

            // Check the tile below.
            if (r < BOARD_SIZE - 1 &&
                board[r][c] == board[r + 1][c])
            {
                return false;
            }
        }
    }

    // No empty spaces or possible merges remain.
    return true;
}
bool save_game(int board[BOARD_SIZE][BOARD_SIZE], int totalScore)
{
    ofstream saveFile("savegame.txt");

    if (!saveFile)
    {
        return false;
    }

    // Save the player's score.
    saveFile << totalScore << endl;

    // Save all 25 board positions.
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            saveFile << board[r][c] << " ";
        }

        saveFile << endl;
    }

    saveFile.close();

    return true;
}

bool load_game(int board[BOARD_SIZE][BOARD_SIZE], int& totalScore)
{
    ifstream saveFile("savegame.txt");

    if (!saveFile)
    {
        return false;
    }

    // Load the saved score.
    if (!(saveFile >> totalScore))
    {
        return false;
    }

    // Load all 25 board positions.
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (!(saveFile >> board[r][c]))
            {
                return false;
            }
        }
    }

    saveFile.close();

    return true;
}
