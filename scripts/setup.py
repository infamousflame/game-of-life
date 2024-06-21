"""Compile the C library."""

from distutils.core import setup, Extension

module = Extension('simulate', sources = ['python_wrappers.c'])

setup(
    name = 'simulate',
    description = "A simulation of Conway's game of life.",
    ext_modules = [module]
)
