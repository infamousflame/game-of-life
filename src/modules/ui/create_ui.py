"""responsible for creating the user interface."""

__all__ = ['MainUI']

from kivy.app import App
from kivy.lang.builder import Builder
from kivy.uix.boxlayout import BoxLayout

from modules.sim.run import board

with open('./assets/ui/root_layout.kv', 'rt') as f:
    Builder.load_string(f.read())


class RootLayout(BoxLayout):
    """The root layout."""


class MainUI(App):
    """The app class."""

    def build(self) -> RootLayout:
        """Build the user interface."""
        self.window: RootLayout = RootLayout()
        self.title = "Conway's Game of Life"
        return self.window
