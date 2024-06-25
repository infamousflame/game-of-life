"""responsible for creating the user interface."""

__all__ = ['MainUI']

from kivy.app import App
from kivy.lang.builder import Builder

from modules.sim.run import board


class MainUI(App):
    """The app class."""

    def build(self):
        """Build the user interface."""
        with open('./assets/ui/root_layout.kv', 'rt') as f:
            return Builder.load_string(f.read())
