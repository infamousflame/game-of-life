"""Compile the C library."""

from os import environ
from setuptools import setup, Extension

if 'VIRTUAL_ENV' not in environ:
    print('Please run this script within a virtual environment.')
    exit(1)

module = Extension('simulate', sources = ['./src/modules/simulate/python_wrappers.c'])

setup(
    name = 'simulate',
    description = "A simulation of Conway's game of life.",
    ext_modules = [module]
)
