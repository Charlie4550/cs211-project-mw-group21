
#include "2048_helper.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void print_board(int board[BOARD_SIZE][BOARD_SIZE])
{
    cout << "\n";

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (board[r][c] == 0)
                cout << ".\t";
            else
                cout << board[r][c] << "\t";
        }

        cout << endl;
    }

    cout << endl;
}

int main()
{
    srand(time(0));

    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    int totalScore = 0;

    add_random_tile(board);
    add_random_tile(board);

    char command;
    bool changed;
    int scoreGained;

    cout << "===== 2048 GAME =====\n";
    cout << "Use W, A, S, D to move.\n";
    cout << "Use P to save your game.\n";
    cout << "Use L to load your saved game.\n";
    cout << "Use Q to quit.\n";

    while (true)
    {
        print_board(board);

        cout << "Score: " << totalScore << endl;
        cout << "Enter move: ";
        cin >> command;

        // Quit the game
        if (command == 'q' || command == 'Q')
        {
            cout << "Thanks for playing!\n";
            break;
        }

        // Save the current game
        if (command == 'p' || command == 'P')
        {
            if (save_game(board, totalScore))
                cout << "Game saved successfully!\n";
            else
                cout << "Error saving game.\n";

            continue;
        }

        // Load a previously saved game
        if (command == 'l' || command == 'L')
        {
            if (load_game(board, totalScore))
                cout << "Game loaded successfully!\n";
            else
                cout << "No saved game found or loading failed.\n";

            continue;
        }

        scoreGained = 0;
        changed = false;

        // Process movement commands
        switch (command)
        {
            case 'a':
            case 'A':
                changed = move_left(board, scoreGained);
                break;

            case 'd':
            case 'D':
                changed = move_right(board, scoreGained);
                break;

            case 'w':
            case 'W':
                changed = move_up(board, scoreGained);
                break;

            case 's':
            case 'S':
                changed = move_down(board, scoreGained);
                break;

            default:
                cout << "Invalid command.\n";
                break;
        }

        // Update the game after a successful move
        if (changed)
        {
            totalScore += scoreGained;

            if (check_win(board))
            {
                print_board(board);
                cout << "Congratulations! You reached 2048!\n";
                cout << "Final score: " << totalScore << endl;
                break;
            }

            add_random_tile(board);
        }

        // Check whether any moves remain
        if (check_game_over(board))
        {
            print_board(board);
            cout << "GAME OVER! No more moves available.\n";
            cout << "Final score: " << totalScore << endl;
            break;
        }

        // Explain when a valid direction does not change the board
        if (!changed &&
            (command == 'a' || command == 'A' ||
             command == 'd' || command == 'D' ||
             command == 'w' || command == 'W' ||
             command == 's' || command == 'S'))
        {
            cout << "That move did not change the board.\n";
        }
    }

    return 0;
}
