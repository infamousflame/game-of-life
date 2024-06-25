"""Compile the C library."""

from setuptools import setup, Extension

module = Extension('simulate', sources = ['./src/modules/simulate/python_wrappers.c'])

setup(
    name = 'simulate',
    description = "A simulation of Conway's game of life.",
    ext_modules = [module]
)
