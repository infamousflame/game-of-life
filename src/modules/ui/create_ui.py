"""responsible for creating the user interface."""

__all__ = ['MainUI']

from kivy.app import App
from kivy.clock import Clock
from kivy.lang.builder import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivy.uix.popup import Popup

from modules.sim_runner.run import board, BOARD_SIZE


class SettingsMenu(Popup):
    """The settings pane."""

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

    def on_release(self) -> None:
        """Handle the press event."""
        board.toggle_cell(*self.coords)
        self.set_bg_color()


class BoardWidget(GridLayout):
    """The board widget."""

    def __init__(self, **kwargs):
        """Initialize the board widget."""
        super().__init__(**kwargs)
        self.cols = BOARD_SIZE[1]
        for i in range(BOARD_SIZE[0]):
            for j in range(BOARD_SIZE[1]):
                self.add_widget(Cell((i, j)))

    def resize(self, rows: int, cols: int) -> None:
        """Resize the board."""
        self.clear_widgets()
        board.resize(rows, cols)
        self.cols = cols
        for i in range(rows):
            for j in range(cols):
                self.add_widget(Cell((i, j)))

    def iterate_once(self) -> None:
        board.iterate_once()
        for child in self.children:
            child.set_bg_color()


class MainUI(App):
    """The app class."""

    def __init__(self, **kwargs) -> None:
        """Initialize the app."""
        super().__init__(**kwargs)
        self.root = None
        self.board_widget = None
        self.title = 'Game of Life'
        self.icon = 'assets/images/icon.ico'

    def build(self):
        """Build the user interface."""
        with open('./assets/ui/ui_layout.kv', 'rt') as f:
            self.root: BoxLayout =  Builder.load_string(f.read())
        self.board_widget = self.root.ids.board_widget
        self.play_pause_button = self.root.ids.play_pause_button
        self.play_pause_callback = (
            lambda *args:
                self.board_widget.iterate_once()
        )
        self.sim_speed: float = 1.0
        return self.root

    def open_settings_menu(self) -> None:
        """Open the settings menu."""
        SettingsMenu().open()

    def play_pause(self) -> None:
        """Play or pause the simulation."""
        if self.play_pause_button.text == "Play":
            Clock.schedule_interval(
                self.play_pause_callback,
                1 / self.sim_speed
            )
            self.play_pause_button.text = "Pause"
        else:
            Clock.unschedule(self.play_pause_callback)
            self.play_pause_button.text = "Play"

