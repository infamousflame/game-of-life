"""responsible for creating the user interface."""

__all__ = ['MainUI']

from kivy.app import App
from kivy.lang.builder import Builder
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout

from modules.sim.run import board, BOARD_SIZE


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

    def __init__(self, **kwargs):
        """Initialize the board widget."""
        super().__init__(**kwargs)
        self.cols = BOARD_SIZE[1]
        self.rows = BOARD_SIZE[0]
        for i in range(BOARD_SIZE[0]):
            for j in range(BOARD_SIZE[1]):
                self.add_widget(Cell((i, j)))


class MainUI(App):
    """The app class."""

    def build(self):
        """Build the user interface."""
        with open('./assets/ui/root_layout.kv', 'rt') as f:
            self.root =  Builder.load_string(f.read())
        self.board_widget = self.root.ids.board_widget
        return self.root

    def iterate_once(self):
        board.iterate_once()
        for child in self.board_widget.children:
            child.set_bg_color()
