"""Testing the resizing capability of the Board class."""

from simulate import Board
from test_sim import print_board


def main() -> None:
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

    board.resize(5, 5)
    print_board(board)

    board.resize(10, 10)
    print_board(board)

if __name__ == '__main__':
    main()
