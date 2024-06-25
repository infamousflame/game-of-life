"""responsible for creating the user interface."""

__all__ = ['MainUI']

from kivy.app import App
from kivy.lang.builder import Builder
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout

from modules.sim_runner.run import board, BOARD_SIZE


class Cell(Button):
    """The cell class."""

    def __init__(self, coords: tuple[int, int], **kwargs) -> None:
        """Initialize the cell."""
        super().__init__(**kwargs)
        self.coords: tuple[int, int] = coords
        self.set_bg_color()

    def set_bg_color(self):
        """Set the background color according to the cell's state."""
        self.background_color = (0, board.get_cell(*self.coords), 0)

    def on_press(self) -> None:
        """Handle the press event."""
        board.set_cell(*self.coords, not board.get_cell(*self.coords))
        self.set_bg_color()


class BoardWidget(GridLayout):
    """The board widget."""

    def __init__(self, rows: int, cols: int, **kwargs):
        """Initialize the board widget."""
        super().__init__(**kwargs)
        self.cols = cols
        for i in range(rows):
            for j in range(cols):
                self.add_widget(Cell((i, j)))

    def resize(self, rows: int, cols: int) -> None:
        """Resize the board."""
        self.clear_widgets()
        self.cols = cols
        for i in range(rows):
            for j in range(cols):
                self.add_widget(Cell((i, j)))


class MainUI(App):
    """The app class."""

    def __init__(self, **kwargs) -> None:
        """Initialize the app."""
        super().__init__(**kwargs)
        self.root = None
        self.board_widget = None
        self.row_slider = None
        self.col_slider = None
        self.title = 'Game of Life'

    def build(self):
        """Build the user interface."""
        with open('./assets/ui/root_layout.kv', 'rt') as f:
            self.root =  Builder.load_string(f.read())
        self.board_widget = BoardWidget(*BOARD_SIZE)
        self.root.add_widget(self.board_widget)
        self.row_slider = self.root.ids.row_slider
        self.col_slider = self.root.ids.col_slider
        return self.root

    def iterate_once(self) -> None:
        board.iterate_once()
        for child in self.board_widget.children:
            child.set_bg_color()

    def resize_board(self) -> None:
        size: tuple[int, int] = self.row_slider.value, self.col_slider.value
        board.resize(*size)
        self.board_widget.resize(*size)
