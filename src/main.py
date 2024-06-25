"""A simple implementation of Conway's game of life."""

__all__ = ['main']
__version__ = '0.0.1'
__author__ = 'Krishna Ranchhod'

from modules.ui.create_ui import MainUI


def main() -> None:
    """The main function."""
    MainUI().run()


if __name__ == '__main__':
    main()
