#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define PLAYER1 'X'
#define PLAYER2 'O'

char board[ROWS][COLS];

void initializeBoard() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = ' ';
}

void displayBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
        printf("%s\n", "-----------------------------");
    }
}

int dropPiece(int col, char player) {
    if (col < 0 || col >= COLS) return 0; // Check for valid column
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return 1; // Piece dropped successfully
        }
    }
    return 0; // Column is full
}

int checkWin(char player) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == player) {
                // Check horizontal
                if (c + 3 < COLS &&
                    board[r][c + 1] == player &&
                    board[r][c + 2] == player &&
                    board[r][c + 3] == player) {
                    return 1;
                }
                // Check vertical
                if (r + 3 < ROWS &&
                    board[r + 1][c] == player &&
                    board[r + 2][c] == player &&
                    board[r + 3][c] == player) {
                    return 1;
                }
                // Check diagonal \
                if (r + 3 < ROWS && c + 3 < COLS &&
                    board[r + 1][c + 1] == player &&
                    board[r + 2][c + 2] == player &&
                    board[r + 3][c + 3] == player) {
                    return 1;
                }
                // Check diagonal /
                if (r - 3 >= 0 && c + 3 < COLS &&
                    board[r - 1][c + 1] == player &&
                    board[r - 2][c + 2] == player &&
                    board[r - 3][c + 3] == player) {
                    return 1;
                }
            }
        }
    }
    return 0; // No win
}

int main() {
    initializeBoard();
    char currentPlayer = PLAYER1;
    int column;

    while (1) {
        displayBoard();
        printf("Player %c, enter column (0-6): ", currentPlayer);
        if (scanf("%d", &column) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (!dropPiece(column, currentPlayer)) {
            printf("Invalid move, try again.\n");
            continue;
        }

        if (checkWin(currentPlayer)) {
            displayBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    return 0;
}
