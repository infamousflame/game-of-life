#include <stdbool.h>
#include <stdlib.h>


/**
 * Allocates memory for a board of size m x n.
 *
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 * @return A pointer to the allocated board.
 */
bool** allocate_board(int m, int n) {
    bool** board = malloc(m * sizeof(bool*));
    for (int i = 0; i < m; i++) {
        board[i] = malloc(n * sizeof(bool));
    }
    return board;
}


/**
 * Frees all pointers in a board.
 *
 * @param board A 2D array of pointers.
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 */
void free_board(bool** board, int m, int n) {
    for (int i = 0; i < m; i++) {
        free(board[i]);
    }
    free(board);
}


/**
 * Initializes all values in a board to false.
 *
 * @param board A pointer to a 2D array of booleans.
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 */
void initialize_board(bool** board, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = false;
        }
    }
}



bool** iterate_once(bool** board, int m, int n) {
    bool** new_board = allocate_board(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int neighbors = 0;
            for (int y = i - 1; y <= i + 1; y++) {
                for (int x = j - 1; x <= j + 1; x++) {
                    if (
                        y >= 0 && y < m && x >= 0 && x < n
                        && !(x == j && y == i) && board[y][x]
                    ) {
                        neighbors++;
                    }
                }
            }
            if (board[i][j]) {
                new_board[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                new_board[i][j] = (neighbors == 3);
            }
        }
    }
    return new_board;
}
