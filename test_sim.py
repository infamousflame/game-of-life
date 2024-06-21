"""This should be a Python equivalent of test_sim.c."""

from time import sleep

from simulate import Board


def print_board(board: Board) -> None:
    """Prints the contents of the board as a 2D boolean array.

    Args:
        board (Board): A Board object representing the game board.
    """
    for i in range(board.get_m()):
        for j in range(board.get_n()):
            print(int(board.get_cell(i, j)), end=' ')
        print()


def main() -> None:
    """Runs a simulation of Conway's Game of Life for 31 iterations.

    This function initializes a 10x10 game board with a specific pattern of alive cells,
    and then iteratively updates the board state until the program is manually stopped.
    The board is printed after each iteration, showing the current state of the game.
    """
    board: Board = Board(10, 10)
    board.set_cell(0, 2, True)
    board.set_cell(1, 0, True)
    board.set_cell(1, 2, True)
    board.set_cell(2, 1, True)
    board.set_cell(2, 2, True)
    board.set_cell(6, 7, True)
    board.set_cell(7, 7, True)
    board.set_cell(8, 7, True)
    print_board(board)

    for i in range(31):
        sleep(1)
        print(f'Iteration {i}:')
        board.iterate_once()
        print_board(board)


if __name__ == '__main__':
    main()
