#include "2048_helper.h"

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
