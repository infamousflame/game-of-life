"""This should be a Python equivalent of test_sim.c."""

from itertools import count
from time import sleep

from simulate import iterate_once


def print_board(board: list[list[bool]]) -> None:
    """Print the given board, where each row is represented by a list of booleans.

    Args:
        board (list[list[bool]]): The board to be printed.
    """
    for row in board:
        for item in row:
            print(int(item), end=' ')
        print()


def main() -> None:
    """Runs the main game loop for Conway's Game of Life.

    This function initializes a 10x10 board with a specific pattern of alive
    cells, then iteratively updates the board state until the program is
    manually stopped. The board is printed after each iteration, showing the
    current state of the game.
    """
    m: int = 10
    n: int = 10
    board: list[list[bool]] = [[False for _ in range(n)] for _ in range(m)]
    board[0][2] = True
    board[1][0] = True
    board[1][2] = True
    board[2][1] = True
    board[2][2] = True
    board[6][7] = True
    board[7][7] = True
    board[8][7] = True
    print_board(board)

    for i in count():
        sleep(1)
        print(f'Iteration {i}:')
        iterate_once(board)
        print_board(board)


if __name__ == '__main__':
    main()
