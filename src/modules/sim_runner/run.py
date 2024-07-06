"""Calls the C extension to run the simulation."""

__all__ = ['board', 'BOARD_SIZE']

from simulate import Board

BOARD_SIZE: tuple[int, int] = (30, 30)

board: Board = Board(*BOARD_SIZE)
