/* A simple implementation of Conway's game of life. */


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
    if (m <= 0 || n <= 0) {
        return NULL;
    }
    bool** board = malloc(m * sizeof(bool*));
    if (board == NULL) {
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        board[i] = malloc(n * sizeof(bool));
        if (board[i] == NULL) {
            // Free already allocated memory
            for (int j = 0; j < i; j++) {
                free(board[j]);
            }
            free(board);
            return NULL;
        }
    }
    return board;
}


/**
 * Reallocates a board of size m x n to a board of size new_m x new_n.
 * Values in the old board are copied to the new board.
 * This does NOT free the old board's pointers.
 *
 * @param board A pointer to a 2D array of booleans.
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 * @param new_m The new number of rows in the new board.
 * @param new_n The new number of columns in the new board.
 * @return A pointer to the newly allocated board.
 */
bool** reallocate_board(bool** board, int m, int n, int new_m, int new_n) {
    bool** new_board = allocate_board(new_m, new_n);
    if (new_board == NULL) {
        return NULL;
    }
    for (int i = 0; i < new_m; i++) {
        if (new_board[i] == NULL) {
            continue;
        }
        for (int j = 0; j < new_n; j++) {
            if (i < m && j < n) {
                new_board[i][j] = board[i][j];
            } else {
                new_board[i][j] = false;
            }
        }
    }
    return new_board;
}


/**
 * Frees all pointers in a board.
 *
 * @param board A pointer to a 2D array of booleans.
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 *
 * @return void
 *
 * @throws None
 */
void free_board(bool** board, int m, int n) {
    if (board == NULL) {
        return;
    }

    for (int i = 0; i < m; i++) {
        if (board[i] == NULL) {
            continue;
        }
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
    if (board == NULL) {
        return;
    }

    for (int i = 0; i < m; i++) {
        if (board[i] == NULL) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            board[i][j] = false;
        }
    }
}


/**
 * Iterates the board once, creates this new board and reutrns a pointer to it.
 *
 * @param board A pointer to a 2D array of booleans.
 * @param m The number of rows in the board.
 * @param n The number of columns in the board.
 * @return A pointer to the new version of the board.
 */
bool** iterate_once(bool** board, int m, int n) {
    if (board == NULL || m <= 0 || n <= 0) {
        return NULL;
    }
    bool** new_board = allocate_board(m, n);
    if (new_board == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < m; i++) {
        if (board[i] == NULL) {
            free_board(new_board, m, n);
            return NULL;
        }
        for (int j = 0; j < n; j++) {
            int neighbors = 0;
            for (int y = i - 1; y <= i + 1; y++) {
                for (int x = j - 1; x <= j + 1; x++) {
                    if (
                        y >= 0 && y < m && x >= 0 && x < n
                        && (y != i || x != j) && board[y][x]
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
