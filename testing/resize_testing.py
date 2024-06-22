"""Testing the resizing capability of the Board class."""

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
    """Initializes a Board object with dimensions 10x10 and sets specific cells to True.
    Prints the initial board state.
    Resizes the board to 5x5 and prints the resized board state.
    Resizes the board back to 10x10 and prints the final board state.
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

    board.resize(5, 5)
    print_board(board)

    board.resize(10, 10)
    print_board(board)

if __name__ == '__main__':
    main()
