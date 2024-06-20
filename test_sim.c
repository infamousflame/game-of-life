// Allows testing basic functions while the GUI is still in development.

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "simulate.c"

void print_board(bool** board, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int m = 10;
    int n = 10;
    bool** board = allocate_board(m, n);
    initialize_board(board, m, n);
    
    board[0][2] = 1;
    board[1][0] = 1;
    board[1][2] = 1;
    board[2][1] = 1;
    board[2][2] = 1;
    board[6][7] = 1;
    board[7][7] = 1;
    board[8][7] = 1;
    
    print_board(board, m, n);

    char* user_input;
    bool** new_board;

    for(int i = 0; ; i++) {
        _sleep(1000);
        printf("Iteration %d:\n", i);
        new_board = iterate_once(board, m, n);
        free_board(board, m, n);
        board = new_board;
        print_board(board, m, n);
    }
    
    free_board(board, m, n);
}
